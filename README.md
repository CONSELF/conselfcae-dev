# CONSELFoam #

CONSELFoam represent a customization made by CONSELF of OpenFOAM.

### How can I install it? ###

Follow the instructions below and modify the path with your local system

```
sed -i "CONSELFoam/d" ~/.bashrc

echo "export CONSELFoamSRC=/path/to/CONSELFoam/directory" >> ~/.bashrc
echo "alias CONSELFoam='source $CONSELFoamSRC/etc/bashrc'" >> ~/.bashrc

cd $CONSELFoamSRC
CONSELFoam
./Allwmake

```

The installation process takes 1/2 hours depending on your system ... so do it at night!

### Using CONSELFoam ###

Before using CONSELFoam you must load its environment on the shell by typing in a shell:

```
CONSELFoam

```

ENJOY!