/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "smooth.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace calcTypes
    {
        defineTypeNameAndDebug(smooth, 0);
        addToRunTimeSelectionTable(calcType, smooth, dictionary);
    }
}


// * * * * * * * * * * * * * * * * t onstructors  * * * * * * * * * * * * * * //

Foam::calcTypes::smooth::smooth()
:
    calcType()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::calcTypes::smooth::~smooth()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::calcTypes::smooth::init()
{
    argList::validArgs.append("smooth");
    argList::validArgs.append("fieldName");
    argList::validOptions.insert("mult","multiplierValueString");
    argList::validOptions.insert("iter","iterationsValueString");
}


void Foam::calcTypes::smooth::preCalc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{}


void Foam::calcTypes::smooth::calc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{
    #ifdef FOAM_DEV
        const word& fieldName = args.additionalArgs()[1];
    #else
        const word fieldName = args[2];
    #endif

    const bool useMult(args.optionReadIfPresent("mult", multValueStr_) );
    const bool useIter(args.optionReadIfPresent("iter", iterValueStr_) );

    IOobject fieldHeader
    (
        fieldName,
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    // Check field exists
    if (fieldHeader.headerOk())
    {
        bool processed = false;

        writeSmoothField<scalar>          ( fieldHeader, mesh, processed, useMult, useIter, multValueStr_, iterValueStr_ );
        writeSmoothField<vector>          ( fieldHeader, mesh, processed, useMult, useIter, multValueStr_, iterValueStr_ );
        writeSmoothField<sphericalTensor> ( fieldHeader, mesh, processed, useMult, useIter, multValueStr_, iterValueStr_ );
        writeSmoothField<symmTensor>      ( fieldHeader, mesh, processed, useMult, useIter, multValueStr_, iterValueStr_ );
        writeSmoothField<tensor>          ( fieldHeader, mesh, processed, useMult, useIter, multValueStr_, iterValueStr_ );

        if (!processed)
        {
            FatalError
                << "Unable to process " << fieldName << nl
                << "No call to smooth for fields of type "
                << fieldHeader.headerClassName() << nl << nl
                << exit(FatalError);
        }
    }
    else
    {
        Info<< "    No " << fieldName << endl;
    }
}


// ************************************************************************* //

