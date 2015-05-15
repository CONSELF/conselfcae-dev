/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
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

Class
    Foam::calcTypes::laplacian

Description
    Smooths the field f iterative by 
    f+=multiplier*C*laplacian(f)
    with
    C=max(mag(f))/max(mag(laplacian(f))

SourceFiles
    smooth.C

\*---------------------------------------------------------------------------*/

#ifndef smooth_H
#define smooth_H

#include "calcType.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

namespace calcTypes
{

/*---------------------------------------------------------------------------*\
                          Class smooth Declaration
\*---------------------------------------------------------------------------*/

class smooth
:
    public calcType
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        smooth(const smooth&);

        //- Disallow default bitwise assignment
        void operator=(const smooth&);

private:

        //- Multiplier for the diffusion/timestep constant
        string multValueStr_;

        //- Amount of iterations
        string iterValueStr_;

protected:

    // Member Functions

        // Calculation routines

            //- Initialise - typically setting static variables,
            //  e.g. command line arguments
            virtual void init();

            //- Pre-time loop calculations
            virtual void preCalc
            (
                const argList& args,
                const Time& runTime,
                const fvMesh& mesh
            );

            //- Time loop calculations
            virtual void calc
            (
                const argList& args,
                const Time& runTime,
                const fvMesh& mesh
            );


        // I-O

            //- Write smooth fields
            template<class Type>
            void writeSmoothField
            (
                const IOobject& header,
                const fvMesh& mesh,
                bool& processed,
                const bool useMult,
                const bool useIter,
                string multValueStr_,
                string iterValueStr_
            );


public:

    //- Runtime type information
    TypeName("smooth");


    // Constructors

        //- Construct null
        smooth();


    //- Destructor
        virtual ~smooth();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace calcTypes
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "writeSmoothField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
