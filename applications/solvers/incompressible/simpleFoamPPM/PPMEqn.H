    // Momentum predictor

    fvScalarMatrix PPMEqn
    (
        fvm::div(phi, PPM)
      - fvm::laplacian(DPPM, PPM)
    );

    PPMEqn.solve();
