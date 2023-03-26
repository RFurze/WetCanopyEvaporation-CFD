{
    alphat = turbulence->nut()/Prt;
    alphat.correctBoundaryConditions();

    volScalarField alphaEff("alphaEff", turbulence->nu()/Pr + alphat);

    fvScalarMatrix SEqn
    (
      fvm::ddt(s)
    + fvm::div(phi, s)
    - fvm::laplacian(Ds, s)
    );

    runTime.write();

    runTime.printExecutionTime(Info);
    
    SEqn.relax();

    fvOptions.constrain(SEqn);

    SEqn.solve();

    radiation->correct();

    fvOptions.correct(s);

}
