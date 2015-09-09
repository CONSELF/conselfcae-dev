# CONSELFoam #

CONSELFoam represent a customization made by CONSELF of OpenFOAM.

### How can I install it? ###

Clone it to any local directory you want. After this, follow the instructions below and modify the path with your local system

```
sed -i "/CONSELFoam/d" ~/.bashrc

echo "export CONSELFoamSRC=/path/to/CONSELFoam/directory" >> ~/.bashrc
echo "alias CONSELFoam='source \$CONSELFoamSRC/etc/bashrc; . \$CONSELFoamSRC/bin/tools/RunFunctions'" >> ~/.bashrc

bash
cd $CONSELFoamSRC
CONSELFoam
./Allwmake

```

The installation process takes between 1 and 2 hours depending on your system ... so do it at night!

### Using CONSELFoam ###

Before using CONSELFoam you must load its environment on the shell by typing in a shell:

```
CONSELFoam

```

### Usefull applications ###

*foamResiduals* -> plot of residuals of current simulation

*foamInstallationTest* -> Installation test of CONSELFoam

*patchSummary* -> Summary of boundary conditions applied to the current case


ENJOY!