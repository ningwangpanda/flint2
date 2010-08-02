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

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    printf("scalar_submul_si_2exp....");
    fflush(stdout);

    _fmpz_vec_randinit();

    // Compare with alternative method of computation
    for (i = 0; i < 10000; i++)
    {
        fmpz *a, *b, *c, *d;
        long len = n_randint(100), x;
        mp_bitcnt_t exp;

        a = _fmpz_vec_init(len);
        b = _fmpz_vec_init(len);
        c = _fmpz_vec_init(len);
        d = _fmpz_vec_init(len);

        _fmpz_vec_randtest(a, len, n_randint(200));
        _fmpz_vec_randtest(b, len, n_randint(200));
        _fmpz_vec_copy(c, b, len);

        x = (long) n_randtest();
        if (n_randint(2))
            x = -x;
        exp = n_randint(200);

        _fmpz_vec_scalar_submul_si_2exp(b, a, len, x, exp);
        _fmpz_vec_scalar_mul_2exp(d, a, len, exp);
        _fmpz_vec_scalar_submul_si(c, d, len, x);

        result = (_fmpz_vec_equal(b, c, len));
        if (!result)
        {
            printf("FAIL:\n");
            printf("x = %ld, exp = %lu\n", x, exp);
            _fmpz_vec_print(b, len), printf("\n\n");
            _fmpz_vec_print(c, len), printf("\n\n");
            abort();
        }

        _fmpz_vec_clear(a, len);
        _fmpz_vec_clear(b, len);
        _fmpz_vec_clear(c, len);
        _fmpz_vec_clear(d, len);
    }

    _fmpz_vec_randclear();
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}