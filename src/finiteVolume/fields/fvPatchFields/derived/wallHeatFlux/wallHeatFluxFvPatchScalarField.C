/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2008 OpenCFD Ltd.
     \\/     M anipulation  | Copyright (C) 2016 CONSELF srl
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "wallHeatFluxFvPatchScalarField.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

wallHeatFluxFvPatchScalarField::wallHeatFluxFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedGradientFvPatchScalarField(p, iF),
    heatFlux_(p.size(), 0.0)
{
}


wallHeatFluxFvPatchScalarField::wallHeatFluxFvPatchScalarField
(
    const wallHeatFluxFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedGradientFvPatchScalarField(ptf, p, iF, mapper),
    heatFlux_(ptf.heatFlux_, mapper)
{}


wallHeatFluxFvPatchScalarField::wallHeatFluxFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedGradientFvPatchScalarField(p, iF),
    heatFlux_("heatFlux", dict, p.size())
{
    if (dict.found("value"))
    {
        fvPatchScalarField::operator=
        (
            scalarField("value", dict, p.size())
        );
    }
    if (dict.found("gradient"))
    {
        gradient() = scalarField("gradient", dict, p.size());
        fixedGradientFvPatchScalarField::updateCoeffs();
        fixedGradientFvPatchScalarField::evaluate();
    }
    else
    {
        fvPatchField<scalar>::operator=(patchInternalField());
        gradient() = 0.0;
    }
}


wallHeatFluxFvPatchScalarField::wallHeatFluxFvPatchScalarField
(
    const wallHeatFluxFvPatchScalarField& wbppsf
)
:
    fixedGradientFvPatchScalarField(wbppsf),
    heatFlux_(wbppsf.heatFlux_)
{}


wallHeatFluxFvPatchScalarField::wallHeatFluxFvPatchScalarField
(
    const wallHeatFluxFvPatchScalarField& wbppsf,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedGradientFvPatchScalarField(wbppsf, iF),
    heatFlux_(wbppsf.heatFlux_)
{
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Update the coefficients associated with the patch field
void wallHeatFluxFvPatchScalarField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const dictionary& transportProperties
        = db().lookupObject<IOdictionary>("transportProperties");

    dimensionedScalar Cp0(transportProperties.lookup("Cp0"));

    dimensionedScalar rho0(transportProperties.lookup("rho0"));

    const fvPatchField<scalar>& alphaEffW =
        patch().lookupPatchField<volScalarField, scalar>("alphaEff");

    gradient() = heatFlux_ / (alphaEffW * Cp0.value() * rho0.value() );

    fixedGradientFvPatchScalarField::updateCoeffs();
}


// Write
void wallHeatFluxFvPatchScalarField::write(Ostream& os) const
{
    fvPatchScalarField::write(os);
    heatFlux_.writeEntry("heatFlux", os);
    gradient().writeEntry("gradient", os);
    this->writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField(fvPatchScalarField, wallHeatFluxFvPatchScalarField);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
