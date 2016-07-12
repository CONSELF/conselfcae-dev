/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2016 OpenFOAM Foundation
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

#include "FUNCTIONOBJECT.H"
<<<<<<< HEAD
#include "dictionary.H"
=======
#include "Time.H"
#include "fvMesh.H"
#include "addToRunTimeSelectionTable.H"
>>>>>>> 90e2f8d87bcd3a8588545c2de68a62d5b5c54a99

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
<<<<<<< HEAD
defineTypeNameAndDebug(FUNCTIONOBJECT, 0);
=======
namespace functionObjects
{
    defineTypeNameAndDebug(FUNCTIONOBJECT, 0);
    addToRunTimeSelectionTable(functionObject, FUNCTIONOBJECT, dictionary);
}
>>>>>>> 90e2f8d87bcd3a8588545c2de68a62d5b5c54a99
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

<<<<<<< HEAD
Foam::FUNCTIONOBJECT::FUNCTIONOBJECT
(
    const word& name,
    const objectRegistry& obr,
    const dictionary& dict,
    const bool loadFromFiles
)
:
    name_(name),
    obr_(obr),
=======
Foam::functionObjects::FUNCTIONOBJECT::FUNCTIONOBJECT
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    fvMeshFunctionObject(name, runTime, dict),
>>>>>>> 90e2f8d87bcd3a8588545c2de68a62d5b5c54a99
    wordData_(dict.lookupOrDefault<word>("wordData", "defaultWord")),
    scalarData_(readScalar(dict.lookup("scalarData"))),
    labelData_(readLabel(dict.lookup("labelData")))
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

<<<<<<< HEAD
Foam::FUNCTIONOBJECT::~FUNCTIONOBJECT()
=======
Foam::functionObjects::FUNCTIONOBJECT::~FUNCTIONOBJECT()
>>>>>>> 90e2f8d87bcd3a8588545c2de68a62d5b5c54a99
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

<<<<<<< HEAD
void Foam::FUNCTIONOBJECT::read(const dictionary& dict)
=======
bool Foam::functionObjects::FUNCTIONOBJECT::read(const dictionary& dict)
>>>>>>> 90e2f8d87bcd3a8588545c2de68a62d5b5c54a99
{
    dict.readIfPresent("wordData", wordData_);
    dict.lookup("scalarData") >> scalarData_;
    dict.lookup("labelData") >> labelData_;
<<<<<<< HEAD
}


void Foam::FUNCTIONOBJECT::execute()
{
    // Do nothing - only valid on write
}


void Foam::FUNCTIONOBJECT::end()
{
    // Do nothing - only valid on write
}


void Foam::FUNCTIONOBJECT::timeSet()
{
    // Do nothing - only valid on write
}


void Foam::FUNCTIONOBJECT::write()
{
=======

    return true;
}


bool Foam::functionObjects::FUNCTIONOBJECT::execute()
{
    return true;
}


bool Foam::functionObjects::FUNCTIONOBJECT::end()
{
    return true;
}


bool Foam::functionObjects::FUNCTIONOBJECT::write()
{
    return true;
>>>>>>> 90e2f8d87bcd3a8588545c2de68a62d5b5c54a99
}


// ************************************************************************* //
