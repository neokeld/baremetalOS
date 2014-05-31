BaremetalOS - baremetal OS pour A20-olinuxino-micro

Créé par : Mathias Brulatout, Arnaud Duforat <neokeld>, Louis Lévèque, Kamal Mallouky

WTF License 2.0, 
Do whatever the f*** you want with the content, EXCEPT claim it as your own work.


Procédure d'installation :

Création d'une micro SD bootable pour A20-olinuxino-micro
=========================================================

Téléchargement de UBoot
-----------------------
    git clone -b sunxi https://github.com/linux-sunxi/u-boot-sunxi.git
    cd u-boot-sunxi

Revenir à une version qui marche
--------------------------------

    git checkout 3d2fc4e8ff764209a8249c3b52dc937f3a106a7f

Compilation
-----------

    make a20-olinuxino_micro CROSS_COMPILE=arm-linux-gnueabihf-
Si le cross-compilateur pour arm n'est pas trouvé
(alors qu'il est installé), quelques liens symboliques règlent le pb :
    ln -s /bin/arm-linux-gnueabi-gcc-4.6 /bin/arm-4.6-linux-gnueabi-gcc

Formater la micro SD (/dev/sdb ici)
-----------------------------------

    fdisk /dev/sdX

Afficher les partitions :

    p enter

Pour effacer la partition :

    d enter 1

Pour les effacer toutes :

    d

Créer la 1ère partition de 16M, commençant en 2048

    n enter p enter 1 enter enter +16M

Créer une 2ème partition avec tout le reste

    n enter p enter 2 enter enter enter

Afficher les partitions :

    p enter

Ça devrait donner :

    Disk /dev/sdb: 3980 MB, 3980394496 bytes
    123 heads, 62 sectors/track, 1019 cylinders, total 7774208 sectors
    Units = sectors of 1 * 512 = 512 bytes
    Sector size (logical/physical): 512 bytes / 512 bytes
    I/O size (minimum/optimal): 512 bytes / 512 bytes
    Disk identifier: 0x00000000
    
    Device Boot Start End Blocks Id System
    
    /dev/sdb1 2048 34815 16384 83 Linux
    /dev/sdb2 34816 7774207 3869696 83 Linux

Sauvegarder :

    w

Formatage des partitions
------------------------

Ensuite on formate la première partition en vfat (ce qui est attendu par le bootloader Allwinner du A20) et la 2ème en ext2 si on veut mettre des binaires dessus :

    mkfs.vfat /dev/sdb1
    mkfs.ext2 /dev/sdb2

Ecrire UBoot sur la micro-SD
----------------------------

*On écrit bien sur /dev/sdb et pas sdb1* :

    dd if=u-boot-sunxi/u-boot-sunxi-with-spl.bin of=/dev/sdb bs=1024 seek=8
    sync

Il ne reste plus qu'à démonter la carte.

Envoyer baremetalOS et l'exécuter sur l'olinuxino
-------------------------------------------------

On compile baremetalOS avec make.

Pour visualiser le boot sur l'olinuxino relié par un USB-port série :

    screen /dev/ttyUSB0 115200

Pour envoyer l'exécutable, on peut utiliser ckermit :
- côté olimex :

    loadb

- côté ordi :

    kermit

Un script le fait avec les bonnes options pour ckermit :

    u-boot-sunxi/tools/scripts/send_image

Ensuite on go à la bonne adresse (le bootelf sur l'adresse de baremetalOS semble ne pas marcher).
On peut aussi mettre l'exécutable sur la 2ème partition de la micro-sd (en ext2)
et faire :

    ext2load mmc 0:2 0x50000000 baremetalOS.bin
    go 0x50000000

Pour exécuter un fichier :

    ./send_image baremetalOS.bin 0x50000000

Une dernière méthode est d'utiliser :

    sudo make send

Quelques commandes de baremetalOS
---------------------------------

Afficher l'aide :

    help

Changer l'état de la LED1 :

    led

Eteindre la LED1 :

    led 0

Allumer la LED1 :

    led 1

Activer la pin p en sortie du gpio n :

    gpio n p

(relancer cette commande désactive la pin p)

Afficher l'état des registres sp, lr et pc :

    reg
