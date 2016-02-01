# CONSELFcae #

CONSELFcae represent a customization made by CONSELF of OpenFOAM® in order to adapt it to CLOUD environment.

### How can I install it? ###

Clone it to any local directory you want. After this, follow the instructions below and modify the path with your local system

```
sed -i "/CONSELFcae/d" ~/.bashrc

echo "export CONSELFcaeSRC=/path/to/CONSELFcae/directory" >> ~/.bashrc
echo "alias CONSELFcae='source \$CONSELFcaeSRC/etc/bashrc; . \$CONSELFcaeSRC/bin/tools/RunFunctions'" >> ~/.bashrc

bash
cd $CONSELFcaeSRC
CONSELFcae
./Allwmake

```

The installation process takes between 1 and 2 hours depending on your system ... so do it at night!

### Using CONSELFcae ###

Before using CONSELFcae you must load its environment on the shell by typing in a shell:

```
CONSELFcae

```

Precompiled version can be found at: [sharing.conself.com/conselfcae](http://sharing.conself.com/conselfcae/)

### Usefull applications ###

*foamResiduals* -> plot of residuals of current simulation

*foamInstallationTest* -> Installation test of CONSELFcae

*patchSummary* -> Summary of boundary conditions applied to the current case

### SYNC WITH OpenFOAM® official repository

It is CONSELF interest to keep the current repository aligned with [OpenFOAM](https://github.com/OpenFOAM/OpenFOAM-dev)® official one.


ENJOY!
