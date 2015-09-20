    // PPM predictor

    fvScalarMatrix PPMEqn
    (
        fvm::div(phi, PPM)
      - fvm::laplacian(DPPM, PPM)
    );

    PPMEqn.relax();

    PPMEqn.solve();
