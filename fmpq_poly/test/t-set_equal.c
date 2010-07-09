
/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/

/******************************************************************************

    Copyright (C) 2010 Sebastian Pancratz
    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"
#include "ulong_extras.h"

int
main (void)
{
    int result;

    printf ("set/equal....");
    fflush (stdout);

    fmpq_poly_randinit ();

    // equal polynomials
    for (ulong i = 0; i < 10000UL; i++)
    {
        fmpq_poly_t a, b;

        fmpq_poly_init (a);
        fmpq_poly_init (b);
        fmpq_poly_randtest (a, n_randint (100), n_randint (200));

        fmpq_poly_set (b, a);

        result = (fmpq_poly_equal (a, b));
        if (!result)
        {
            printf ("Error:\n");
            printf ("a = ");
            fmpq_poly_print (a);
            printf ("\n");
            printf ("alloc = %lu\nlength = %lu\n\n", a->alloc, a->length);
            printf ("b = ");
            fmpq_poly_print (b);
            printf ("\n\n");
            printf ("alloc = %lu\nlength = %lu\n\n", b->alloc, b->length);
            printf ("equal(a, b) = %i\n", result);
            abort ();
        }

        fmpq_poly_clear (a);
        fmpq_poly_clear (b);
    }

    for (ulong i = 0; i < 10000UL; i++)
    {
        fmpq_poly_t a, b;

        ulong coeff = n_randint (100);

        mpq_t x1, x2;

        fmpz_t x1fmpz;

        mpq_init (x1);
        mpq_init (x2);
        fmpz_init (x1fmpz);
        fmpq_poly_init (a);
        fmpq_poly_init (b);
        fmpq_poly_randtest (a, n_randint (100), n_randint (200));

        fmpq_poly_set (b, a);

        fmpq_poly_get_coeff_mpq (x2, b, coeff);
        do
        {
            fmpz_randtest (x1fmpz, 200);
            fmpz_get_mpz (mpq_numref (x1), x1fmpz);
            mpz_set_si (mpq_denref (x1), 1);
        } while (mpq_equal (x1, x2));
        fmpq_poly_set_coeff_mpq (b, coeff, x1);

        result = (!fmpq_poly_equal (a, b));
        if (!result)
        {
            printf ("Error:\n");
            printf ("a = ");
            fmpq_poly_print (a);
            printf ("\n");
            printf ("alloc = %lu\nlength = %lu\n\n", a->alloc, a->length);
            printf ("b = ");
            fmpq_poly_print (b);
            printf ("\n\n");
            printf ("alloc = %lu\nlength = %lu\n\n", b->alloc, b->length);
            printf ("!equal(a, b) = %i\n", result);
            abort ();
        }

        mpq_clear (x1);
        mpq_clear (x2);
        fmpz_clear (x1fmpz);
        fmpq_poly_clear (a);
        fmpq_poly_clear (b);
    }

    fmpq_poly_randclear ();

    _fmpz_cleanup ();
    printf ("PASS\n");
    return 0;
}