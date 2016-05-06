
if (Pstream::master())
{
    ensightCaseFile << nl << "TIME" << nl
        << "time set:                      " << 1 << nl
        << "number of steps:               " << nTimeSteps << nl
        << "filename start number:         " << 0 << nl
        << "filename increment:            " << 1 << nl;

    ensightCaseFile << "time values:" << nl;

    ensightCaseFile.setf(ios_base::scientific, ios_base::floatfield);
    ensightCaseFile.precision(5);

    //label count = 0;
    scalar Tcorr = 0.0;
    if (Times[0].value() < 0)
    {
        Tcorr = - Times[0].value();
        Info<< "Correcting time values. Adding " << Tcorr << endl;
    }

    forAll(Times, n)
    {
        double current_time = Times[n].value() + Tcorr;

        std::ostringstream sstream;
        sstream << current_time;
        std::string Tmp = sstream.str();

        //ensightCaseFile << std::fixed << setw(12) << Times[n].value() + Tcorr << nl;
        ensightCaseFile << Tmp.c_str() << nl;
    }

    ensightCaseFile << nl;
}
