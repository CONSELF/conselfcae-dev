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

#include "grad.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace calcTypes
    {
        defineTypeNameAndDebug(grad, 0);
        addToRunTimeSelectionTable(calcType, grad, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::calcTypes::grad::grad()
:
    calcType()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::calcTypes::grad::~grad()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::calcTypes::grad::init()
{
    argList::validArgs.append("grad");
    argList::validArgs.append("fieldName");
}


void Foam::calcTypes::grad::preCalc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{}


void Foam::calcTypes::grad::calc
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

        writeGradField<scalar,volVectorField>(fieldHeader, mesh, processed);
        writeGradField<vector,volTensorField>(fieldHeader, mesh, processed);

        if (!processed)
        {
            FatalError
                << "Unable to process " << fieldName << nl
                << "No call to grad for fields of type "
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

