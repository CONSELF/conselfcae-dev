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

#include "multiplyDivide.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace calcTypes
    {
        defineTypeNameAndDebug(multiplyDivide, 0);
        addToRunTimeSelectionTable(calcType, multiplyDivide, dictionary);
    }
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::calcTypes::multiplyDivide::writeMultiplyDivideFields
(
    const Time& runTime,
    const fvMesh& mesh,
    const IOobject& baseFieldHeader
)
{
    bool processed = false;

    IOobject multiplyDivideFieldHeader
    (
        multiplyDivideFieldName_,
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    if (multiplyDivideFieldHeader.headerOk())
    {
        writeMultiplyDivideField<scalar>
        (
            baseFieldHeader,
            multiplyDivideFieldHeader,
            mesh,
            processed
        );
        writeMultiplyDivideField<vector>
        (
            baseFieldHeader,
            multiplyDivideFieldHeader,
            mesh,
            processed
        );
        writeMultiplyDivideField<sphericalTensor>
        (
            baseFieldHeader,
            multiplyDivideFieldHeader,
            mesh,
            processed
        );
        writeMultiplyDivideField<symmTensor>
        (
            baseFieldHeader,
            multiplyDivideFieldHeader,
            mesh,
            processed
        );
        writeMultiplyDivideField<tensor>
        (
            baseFieldHeader,
            multiplyDivideFieldHeader,
            mesh,
            processed
        );

        if (!processed)
        {
            FatalError
                << "Unable to process " << baseFieldName_
                << " + " << multiplyDivideFieldName_ << nl
                << "No call to multiplyDivide for fields of type "
                << baseFieldHeader.headerClassName() << " + "
                << multiplyDivideFieldHeader.headerClassName() << nl << nl
                << exit(FatalError);
        }
    }
    else
    {
        FatalErrorIn("calcTypes::multiplyDivide::writeMultiplyDivideFields()")
            << "Unable to read multiplyDivide field: " << multiplyDivideFieldName_
            << nl << exit(FatalError);
    }
}


void Foam::calcTypes::multiplyDivide::writeMultiplyDivideValues
(
    const Time& runTime,
    const fvMesh& mesh,
    const IOobject& baseFieldHeader
)
{
    bool processed = false;

    writeMultiplyDivideValue<scalar>
    (
        baseFieldHeader,
        multiplyDivideValueStr_,
        mesh,
        processed
    );
    writeMultiplyDivideValue<vector>
    (
        baseFieldHeader,
        multiplyDivideValueStr_,
        mesh,
        processed
    );
    writeMultiplyDivideValue<sphericalTensor>
    (
        baseFieldHeader,
        multiplyDivideValueStr_,
        mesh,
        processed
    );
    writeMultiplyDivideValue<symmTensor>
    (
        baseFieldHeader,
        multiplyDivideValueStr_,
        mesh,
        processed
    );
    writeMultiplyDivideValue<tensor>
    (
        baseFieldHeader,
        multiplyDivideValueStr_,
        mesh,
        processed
    );

    if (!processed)
    {
        FatalErrorIn("calcTypes::multiplyDivide::writeMultiplyDivideValue()")
            << "Unable to process " << baseFieldName_
            << " + " << multiplyDivideValueStr_ << nl
            << "No call to multiplyDivide for fields of type "
            << baseFieldHeader.headerClassName() << nl << nl
            << exit(FatalError);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::calcTypes::multiplyDivide::multiplyDivide()
:
    calcType(),
    baseFieldName_(""),
    calcType_(FIELD),
    multiplyDivideFieldName_(""),
    multiplyDivideValueStr_(""),
    resultName_(""),
    calcMode_(MULTIPLY)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::calcTypes::multiplyDivide::~multiplyDivide()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::calcTypes::multiplyDivide::init()
{
    argList::validArgs.append("multiply");
    argList::validArgs.append("baseField");
    argList::validArgs.append("calcMode");
    argList::validOptions.insert("field", "fieldName");
    argList::validOptions.insert("value", "valueString");
    argList::validOptions.insert("resultName", "fieldName");
}


void Foam::calcTypes::multiplyDivide::preCalc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{
    #ifdef FOAM_DEV
        baseFieldName_ = args.additionalArgs()[1];
        word calcModeName = args.additionalArgs()[2];
    #else
        baseFieldName_ = args[2];
        const word calcModeName = args[3];
    #endif

    if (calcModeName == "multiply")
    {
        calcMode_ = MULTIPLY;
    }
    else if (calcModeName == "divide")
    {
        calcMode_ = DIVIDE;
    }
    else
    {
        FatalErrorIn("calcTypes::multiplyDivide::preCalc")
            << "Invalid calcMode: " << calcModeName << nl
            << "    Valid calcModes are multiply and divide" << nl
            << exit(FatalError);
    }

#ifdef FOAM_DEV
    if (args.optionFound("field"))
    {
        multiplyDivideFieldName_ = args.option("field");
        calcType_ = FIELD;
    }
    else if (args.optionFound("value"))
    {
        multiplyDivideValueStr_ = args.option("value");
        calcType_ = VALUE;
    }
#else
    if (args.optionReadIfPresent("field", multiplyDivideFieldName_))
    {
        calcType_ = FIELD;
    }
    else if (args.optionReadIfPresent("value", multiplyDivideValueStr_))
    {
        calcType_ = VALUE;
    }
#endif
    else
    {
        FatalErrorIn("calcTypes::multiplyDivide::preCalc")
            << "multiplyDivide requires either -field or -value option"
            << nl << exit(FatalError);
    }
#ifdef FOAM_DEV
    if (args.optionFound("resultName"))
    {
        resultName_ = args.option("resultName");
    }
#else
    args.optionReadIfPresent("resultName", resultName_);
#endif
}


void Foam::calcTypes::multiplyDivide::calc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{
    IOobject baseFieldHeader
    (
        baseFieldName_,
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    if (baseFieldHeader.headerOk())
    {
        switch (calcType_)
        {
            case FIELD:
            {
                writeMultiplyDivideFields(runTime, mesh, baseFieldHeader);
                break;
            }
            case VALUE:
            {
                writeMultiplyDivideValues(runTime, mesh, baseFieldHeader);
                break;
            }
            default:
            {
                FatalErrorIn("calcTypes::multiplyDivide::calc")
                    << "unknown calcType " << calcType_ << nl
                    << abort(FatalError);
            }
        }
    }
    else
    {
        FatalErrorIn("calcTypes::multiplyDivide::calc")
            << "Unable to read base field: " << baseFieldName_
            << nl << exit(FatalError);
    }
}


// ************************************************************************* //

