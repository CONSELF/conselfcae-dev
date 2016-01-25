# CONSELFcloud #

CONSELFcloud represent a customization made by CONSELF of OpenFOAM® in order to adapt it to CLOUD environment.

### How can I install it? ###

Clone it to any local directory you want. After this, follow the instructions below and modify the path with your local system

```
sed -i "/CONSELFcloud/d" ~/.bashrc

echo "export CONSELFcloudSRC=/path/to/CONSELFcloud/directory" >> ~/.bashrc
echo "alias CONSELFcloud='source \$CONSELFcloudSRC/etc/bashrc; . \$CONSELFcloudSRC/bin/tools/RunFunctions'" >> ~/.bashrc

bash
cd $CONSELFcloudSRC
CONSELFcloud
./Allwmake

```

The installation process takes between 1 and 2 hours depending on your system ... so do it at night!

### Using CONSELFcloud ###

Before using CONSELFcloud you must load its environment on the shell by typing in a shell:

```
CONSELFcloud

```

Precompiled version can be found at: [sharing.conself.com/conselfcloud](http://sharing.conself.com/conselfcloud/)

### Usefull applications ###

*foamResiduals* -> plot of residuals of current simulation

*foamInstallationTest* -> Installation test of CONSELFcloud

*patchSummary* -> Summary of boundary conditions applied to the current case

### SYNC WITH OpenFOAM® official repository

It is CONSELF interest to keep the current repository aligned with [OpenFOAM](https://github.com/OpenFOAM/OpenFOAM-dev)® official one.


ENJOY!
