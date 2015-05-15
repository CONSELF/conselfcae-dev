/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenCFD Ltd.
     \\/     M anipulation  | A.Kidess@tudelft.nl
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

#include "maxAbs.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace calcTypes
    {
        defineTypeNameAndDebug(maxAbs, 0);
        addToRunTimeSelectionTable(calcType, maxAbs, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::calcTypes::maxAbs::maxAbs()
:
    calcType()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::calcTypes::maxAbs::~maxAbs()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::calcTypes::maxAbs::init()
{
    argList::validArgs.append("maxAbs");
    argList::validArgs.append("fieldName");
}


void Foam::calcTypes::maxAbs::preCalc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{}


void Foam::calcTypes::maxAbs::calc
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

        writeMaxField<scalar>(fieldHeader, mesh, processed);
        writeMaxField<vector>(fieldHeader, mesh, processed);
        writeMaxField<sphericalTensor>(fieldHeader, mesh, processed);
        writeMaxField<symmTensor>(fieldHeader, mesh, processed);
        writeMaxField<tensor>(fieldHeader, mesh, processed);

        if (!processed)
        {
            FatalError
                << "Unable to process " << fieldName << nl
                << "No call to maxAbs for fields of type "
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

