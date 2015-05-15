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

template<class Type>
void Foam::calcTypes::smooth::writeSmoothField
(
    const IOobject& header,
    const fvMesh& mesh,
    bool& processed,
    const bool useMult,
    const bool useIter,
    string multValueStr_,
    string iterValueStr_
)
{
    typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

    if (header.headerClassName() == fieldType::typeName)
    {
        Info<< "    Reading " << header.name() << endl;
        fieldType field(header, mesh);

        scalar multiplier(0.1);
        if ( useMult) IStringStream(multValueStr_)() >> multiplier;

        int totIter(10);
        if ( useIter ) IStringStream(iterValueStr_)() >> totIter;

        Info<< "    Using " << totIter << " iterations with multiplier " << multiplier << endl;

        dimensionedScalar C(0.1*max(mag(field))/max(mag(fvc::laplacian(field))));
        fieldType smoothField
        (
            IOobject
            (
                "smooth" + header.name(),
                mesh.time().timeName(),
                mesh,
                IOobject::NO_READ
            ),
            field
        );

        for( int i = 0; i<totIter; i++)
        {
            C=(multiplier*mag(max(smoothField))/mag(max(fvc::laplacian(smoothField))));
            Info<< "    Iteration: " << i << " with C " << C.value() << endl;
            smoothField+=C*fvc::laplacian(smoothField);
            smoothField.correctBoundaryConditions();
        }

        smoothField.write();

        processed = true;
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
