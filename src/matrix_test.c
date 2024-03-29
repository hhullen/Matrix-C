#include "matrix.h"

#include <check.h>

START_TEST(create_1) {
  matrix_t A;
  A = create_matrix(3, 4);
  int res = 1, res1 = 1;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      if (A.matrix[i][j] != 0.0) {
        res = 0;
      }
    }
  }
  if (A.matrix_type != ZERO_MATRIX) {
    res1 = 0;
  }
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(res1, 1);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 4);
  remove_matrix(&A);
}
END_TEST

START_TEST(create_2) {
  matrix_t A;
  A = create_matrix(0, -1);
  int res = 1;
  if (A.matrix_type != INCORRECT_MATRIX) {
    res = 0;
  }
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(create_3) {
  matrix_t a = {0};
  a = create_matrix(1, 1);
  ck_assert_int_eq(a.matrix_type, ZERO_MATRIX);
  matrix_t a1 = {0};
  a1 = create_matrix(-1, -2);
  ck_assert_int_eq(a1.matrix_type, INCORRECT_MATRIX);
  remove_matrix(&a);
}
END_TEST

START_TEST(rem_1) {
  matrix_t a = create_matrix(1, 1);
  remove_matrix(&a);
  ck_assert_int_eq(a.rows, FAILURE);
  ck_assert_int_eq(a.columns, FAILURE);
}
END_TEST

START_TEST(eq_1) {
  matrix_t A, B, C, D;
  A = create_matrix(2, 3);
  B = create_matrix(2, 3);
  C = create_matrix(2, 3);
  D = create_matrix(1, 3);
  A.matrix[0][0] = 1.3455;
  A.matrix[0][1] = 4.2;
  A.matrix[0][2] = 3.4334;
  A.matrix[1][0] = 2.33;
  A.matrix[1][1] = 5.345;
  A.matrix[1][2] = 6.1;
  A.matrix_type = 0;
  B.matrix[0][0] = 1.3455;
  B.matrix[0][1] = 4.2;
  B.matrix[0][2] = 3.4334;
  B.matrix[1][0] = 2.33;
  B.matrix[1][1] = 5.345;
  B.matrix[1][2] = 6.1;
  B.matrix_type = 0;
  C.matrix[0][0] = 1.345;
  C.matrix[0][1] = 4.2;
  C.matrix[0][2] = 3.4334;
  C.matrix[1][0] = 2.33;
  C.matrix[1][1] = 5.345;
  C.matrix[1][2] = 6.1;
  D.matrix[0][0] = 1.35;
  D.matrix[0][1] = 4.2;
  D.matrix[0][2] = 3.44;
  D.matrix_type = 0;
  int res = eq_matrix(&A, &B);
  int res1 = eq_matrix(&A, &C);
  int res2 = eq_matrix(&A, &D);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(eq_2) {
  matrix_t a = create_matrix(1, 1);
  matrix_t b = create_matrix(1, 1);
  ck_assert_int_eq(eq_matrix(&a, &b), SUCCESS);
  a.matrix[0][0] = 2;
  ck_assert_int_eq(eq_matrix(&a, &b), FAILURE);
  b.matrix[0][0] = 2.000000001;
  ck_assert_int_eq(eq_matrix(&a, &b), SUCCESS);
  b.matrix[0][0] = 2.00000002;
  ck_assert_int_eq(eq_matrix(&a, &b), SUCCESS);
  matrix_t c = create_matrix(2, 1);
  c.matrix[0][0] = 2;
  ck_assert_int_eq(eq_matrix(&a, &c), FAILURE);
  matrix_t d = create_matrix(1, 1);
  d.matrix[0][0] = 2;
  d.matrix_type = 2;
  ck_assert_int_eq(eq_matrix(&a, &d), 1);
  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&c);
  remove_matrix(&d);
}
END_TEST

START_TEST(sum_1) {
  matrix_t A, B, C, D, E, F;
  A = create_matrix(2, 3);
  B = create_matrix(2, 3);
  C = create_matrix(2, 3);
  E = create_matrix(2, 2);
  A.matrix[0][0] = 1.3455;
  A.matrix[0][1] = 4.2;
  A.matrix[0][2] = 3.4334;
  A.matrix[1][0] = 2.33;
  A.matrix[1][1] = 5.345;
  A.matrix[1][2] = 6.1;
  A.matrix_type = 0;
  B.matrix[0][0] = 1.3436;
  B.matrix[0][1] = 3.23;
  B.matrix[0][2] = 3.434;
  B.matrix[1][0] = 2.3663;
  B.matrix[1][1] = 5.345;
  B.matrix[1][2] = 4.134;
  B.matrix_type = 0;
  C.matrix[0][0] = 2.6891;
  C.matrix[0][1] = 7.43;
  C.matrix[0][2] = 6.8674;
  C.matrix[1][0] = 4.6963;
  C.matrix[1][1] = 10.69;
  C.matrix[1][2] = 10.234;
  C.matrix_type = 0;
  D = sum_matrix(&A, &B);
  F = sum_matrix(&A, &E);
  int res = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(D.matrix_type, 0);
  ck_assert_int_eq(F.matrix_type, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
  remove_matrix(&F);
}
END_TEST

START_TEST(sum_2) {
  matrix_t a = create_matrix(2, 2);
  matrix_t b = create_matrix(2, 2);
  a.matrix[0][0] = 1;
  a.matrix[1][1] = 1;
  matrix_t c = sum_matrix(&a, &b);
  ck_assert_int_eq(c.matrix_type, IDENTITY_MATRIX);
  remove_matrix(&c);

  matrix_t d = create_matrix(2, 3);
  c = sum_matrix(&a, &d);
  ck_assert_int_eq(c.matrix_type, INCORRECT_MATRIX);
  remove_matrix(&c);

  matrix_t f = create_matrix(2, 2);
  c = sum_matrix(&a, &f);
  ck_assert_int_eq(c.matrix_type, 2);
  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&c);
  remove_matrix(&d);
  remove_matrix(&f);
}
END_TEST

START_TEST(sub_1) {
  matrix_t A, B, C, D, E, F;
  A = create_matrix(3, 3);
  B = create_matrix(3, 3);
  C = create_matrix(3, 3);
  E = create_matrix(2, 2);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 2.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 2.0;
  A.matrix_type = 0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = 1.0;
  B.matrix[1][2] = 0.0;
  B.matrix[2][0] = 0.0;
  B.matrix[2][1] = 0.0;
  B.matrix[2][2] = 1.0;
  B.matrix_type = 0;
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = 0.0;
  C.matrix[0][2] = 0.0;
  C.matrix[1][0] = 0.0;
  C.matrix[1][1] = 1.0;
  C.matrix[1][2] = 0.0;
  C.matrix[2][0] = 0.0;
  C.matrix[2][1] = 0.0;
  C.matrix[2][2] = 1.0;
  C.matrix_type = 2;
  D = sub_matrix(&A, &B);
  F = sub_matrix(&A, &E);
  int res = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(D.matrix_type, 2);
  ck_assert_int_eq(F.matrix_type, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
  remove_matrix(&F);
}
END_TEST

START_TEST(sub_2) {
  matrix_t A, B, C, D;
  A = create_matrix(3, 3);
  B = create_matrix(3, 3);
  C = create_matrix(3, 3);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = -1.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = -1.0;
  A.matrix_type = 0;
  B.matrix[0][0] = -1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = -1.0;
  B.matrix[1][2] = 0.0;
  B.matrix[2][0] = 0.0;
  B.matrix[2][1] = 0.0;
  B.matrix[2][2] = -1.0;
  B.matrix_type = 0;
  D = sub_matrix(&A, &B);
  int res = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(D.matrix_type, 3);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(sub_3) {
  matrix_t a = create_matrix(2, 2);
  matrix_t b = create_matrix(2, 2);
  a.matrix[0][0] = 2;
  a.matrix[1][1] = 2;
  b.matrix[0][0] = 1;
  b.matrix[1][1] = 1;
  matrix_t c;
  c = sub_matrix(&a, &b);
  ck_assert_int_eq(c.matrix_type, IDENTITY_MATRIX);
  remove_matrix(&c);
  matrix_t d = create_matrix(2, 3);
  c = sub_matrix(&a, &d);
  ck_assert_int_eq(c.matrix_type, 1);
  remove_matrix(&c);
  matrix_t f = create_matrix(2, 2);
  remove_matrix(&f);
  f.matrix_type = INCORRECT_MATRIX;
  c = sub_matrix(&a, &f);
  ck_assert_int_eq(c.matrix_type, INCORRECT_MATRIX);
  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&c);
  remove_matrix(&d);
}
END_TEST

START_TEST(mult_num_1) {
  matrix_t A, B, D;
  double x = 3.45;
  A = create_matrix(2, 2);
  B = create_matrix(2, 2);
  A.matrix[0][0] = 2.987654;
  A.matrix[0][1] = -5.3456;
  A.matrix[1][0] = 6.23;
  A.matrix[1][1] = -3.9292;
  A.matrix_type = 0;
  B.matrix[0][0] = 10.3074063;
  B.matrix[0][1] = -18.44232;
  B.matrix[1][0] = 21.4935;
  B.matrix[1][1] = -13.55574;
  B.matrix_type = 0;
  D = mult_number(&A, x);
  int res = eq_matrix(&D, &B);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&D);
}
END_TEST

START_TEST(mult_num_2) {
  matrix_t a = create_matrix(2, 2);
  matrix_t c;
  a.matrix[0][0] = 1;
  a.matrix[1][1] = 1;
  c = mult_number(&a, 1);
  ck_assert_int_eq(c.matrix_type, IDENTITY_MATRIX);
  remove_matrix(&c);
  c = mult_number(&a, 2);
  int check = 0;
  for (int i = 0; i < c.rows; i++) {
    for (int j = 0; j < c.columns; j++) {
      if (c.matrix[i][j] != (a.matrix[i][j] * 2)) {
        check = 1;
        break;
      }
      if (check) {
        break;
      }
    }
  }
  remove_matrix(&c);
  ck_assert_int_eq(check, FAILURE);
  remove_matrix(&a);
  a.matrix_type = INCORRECT_MATRIX;
  c = mult_number(&a, 2);
  ck_assert_int_eq(c.matrix_type, INCORRECT_MATRIX);
  remove_matrix(&c);
}
END_TEST

START_TEST(mult_m_1) {
  matrix_t A, B, C, D, E, F;
  A = create_matrix(2, 2);
  B = create_matrix(2, 4);
  C = create_matrix(2, 4);
  E = create_matrix(4, 2);
  A.matrix[0][0] = 2.987654;
  A.matrix[0][1] = -5.3456;
  A.matrix[1][0] = 6.23;
  A.matrix[1][1] = -3.9292;
  A.matrix_type = 0;
  B.matrix[0][0] = 4.838;
  B.matrix[0][1] = 8.0987;
  B.matrix[0][2] = 8.09;
  B.matrix[0][3] = -987;
  B.matrix[1][0] = -8;
  B.matrix[1][1] = -0.921;
  B.matrix[1][2] = -0.91;
  B.matrix[1][3] = 21;
  B.matrix_type = 0;
  C.matrix[0][0] = 57.219070052;
  C.matrix[0][1] = 29.1194110498;
  C.matrix[0][2] = 29.03461686;
  C.matrix[0][3] = -3061.072098;
  C.matrix[1][0] = 61.57434;
  C.matrix[1][1] = 54.0736942;
  C.matrix[1][2] = 53.976272;
  C.matrix[1][3] = -6231.5232;
  C.matrix_type = 0;
  D = mult_matrix(&A, &B);
  F = mult_matrix(&A, &E);
  int res = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(C.matrix_type, 0);
  ck_assert_int_eq(F.matrix_type, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
  remove_matrix(&F);
}
END_TEST

START_TEST(mult_m_2) {
  matrix_t a = create_matrix(3, 2);
  matrix_t b = create_matrix(2, 3);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 4;
  a.matrix[1][0] = 2;
  a.matrix[1][1] = 5;
  a.matrix[2][0] = 3;
  a.matrix[2][1] = 6;
  b.matrix[0][0] = 1;
  b.matrix[0][1] = -1;
  b.matrix[0][2] = 1;
  b.matrix[1][0] = 2;
  b.matrix[1][1] = 3;
  b.matrix[1][2] = 4;
  matrix_t res = create_matrix(3, 3);
  res.matrix[0][0] = 9;
  res.matrix[0][1] = 11;
  res.matrix[0][2] = 17;
  res.matrix[1][0] = 12;
  res.matrix[1][1] = 13;
  res.matrix[1][2] = 22;
  res.matrix[2][0] = 15;
  res.matrix[2][1] = 15;
  res.matrix[2][2] = 27;
  matrix_t c = mult_matrix(&a, &b);
  int check = 0;
  for (int i = 0; i < c.rows; i++) {
    for (int j = 0; j < c.columns; j++) {
      if (c.matrix[i][j] != res.matrix[i][j]) {
        check = 1;
        break;
      }
      if (check) {
        break;
      }
    }
  }
  remove_matrix(&c);
  ck_assert_int_eq(check, FAILURE);
  remove_matrix(&a);
  a.matrix_type = INCORRECT_MATRIX;
  c = mult_matrix(&a, &b);
  ck_assert_int_eq(c.matrix_type, INCORRECT_MATRIX);
  remove_matrix(&c);
  remove_matrix(&b);
  remove_matrix(&res);
  matrix_t m1 = create_matrix(3, 1);
  remove_matrix(&m1);
  m1.matrix_type = INCORRECT_MATRIX;
  matrix_t m2 = create_matrix(2, 4);
  matrix_t m3 = mult_matrix(&m1, &m2);
  ck_assert_int_eq(m3.matrix_type, INCORRECT_MATRIX);
  remove_matrix(&m3);
  remove_matrix(&m2);
}
END_TEST

START_TEST(trans_1) {
  matrix_t A, B, C;
  A = create_matrix(3, 3);
  C = create_matrix(3, 3);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 2.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 2.0;
  A.matrix_type = 0;
  B = transpose(&A);
  C.matrix[0][0] = 2.0;
  C.matrix[0][1] = 0.0;
  C.matrix[0][2] = 0.0;
  C.matrix[1][0] = 0.0;
  C.matrix[1][1] = 2.0;
  C.matrix[1][2] = 0.0;
  C.matrix[2][0] = 0.0;
  C.matrix[2][1] = 0.0;
  C.matrix[2][2] = 2.0;
  C.matrix_type = 0;
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(trans_2) {
  matrix_t a = create_matrix(2, 1);
  matrix_t b = create_matrix(1, 2);
  a.matrix[0][0] = 1;
  a.matrix[1][0] = 2;
  a.matrix_type = 0;
  b.matrix[0][0] = 1;
  b.matrix[0][1] = 2;
  b.matrix_type = 0;
  matrix_t c = transpose(&a);
  ck_assert_int_eq(eq_matrix(&b, &c), SUCCESS);
  remove_matrix(&c);
  remove_matrix(&a);
  a.matrix_type = INCORRECT_MATRIX;
  c = transpose(&a);
  ck_assert_int_eq(eq_matrix(&b, &c), FAILURE);
  remove_matrix(&c);
  remove_matrix(&b);
}
END_TEST

START_TEST(calc_compl_1) {
  matrix_t A, B, C, D, E;
  A = create_matrix(3, 3);
  C = create_matrix(3, 3);
  D = create_matrix(2, 3);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  A.matrix_type = 0;
  B = calc_complements(&A);
  C.matrix[0][0] = 0.0;
  C.matrix[0][1] = 10.0;
  C.matrix[0][2] = -20.0;
  C.matrix[1][0] = 4.0;
  C.matrix[1][1] = -14.0;
  C.matrix[1][2] = 8.0;
  C.matrix[2][0] = -8.0;
  C.matrix[2][1] = -2.0;
  C.matrix[2][2] = 4.0;
  C.matrix_type = 0;
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(B.matrix_type, 0);
  E = calc_complements(&D);
  ck_assert_int_eq(E.matrix_type, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
}
END_TEST

START_TEST(calc_compl_2) {
  matrix_t a = create_matrix(3, 3);
  matrix_t res = create_matrix(3, 3);
  matrix_t m;
  res.matrix[0][0] = 0;
  res.matrix[0][1] = 10;
  res.matrix[0][2] = -20;
  res.matrix[1][0] = 4;
  res.matrix[1][1] = -14;
  res.matrix[1][2] = 8;
  res.matrix[2][0] = -8;
  res.matrix[2][1] = -2;
  res.matrix[2][2] = 4;
  res.matrix_type = 0;
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  a.matrix_type = 0;
  m = calc_complements(&a);
  ck_assert_int_eq(eq_matrix(&res, &m), SUCCESS);
  remove_matrix(&m);
  remove_matrix(&a);
  a.matrix_type = INCORRECT_MATRIX;
  m = calc_complements(&a);
  ck_assert_int_eq(eq_matrix(&res, &m), FAILURE);
  remove_matrix(&m);
  remove_matrix(&res);
}
END_TEST

START_TEST(determ_1) {
  matrix_t A, B, C, D;
  A = create_matrix(2, 2);
  B = create_matrix(2, 4);
  C = create_matrix(1, 1);
  D = create_matrix(3, 3);
  A.matrix[0][0] = 2.987654;
  A.matrix[0][1] = -5.3456;
  A.matrix[1][0] = 6.23;
  A.matrix[1][1] = -3.9292;
  A.matrix_type = 0;
  B.matrix[0][0] = 4.838;
  B.matrix[0][1] = 8.0987;
  B.matrix[0][2] = 8.09;
  B.matrix[0][3] = -987;
  B.matrix[1][0] = -8;
  B.matrix[1][1] = -0.921;
  B.matrix[1][2] = -0.91;
  B.matrix[1][3] = 21;
  B.matrix_type = 0;
  C.matrix[0][0] = 2.32443;
  D.matrix[0][0] = 2.8;
  D.matrix[0][1] = 1.3;
  D.matrix[0][2] = 7.01;
  D.matrix[1][0] = -1.03;
  D.matrix[1][1] = -2.3;
  D.matrix[1][2] = 3.01;
  D.matrix[2][0] = 0;
  D.matrix[2][1] = -3;
  D.matrix[2][2] = 2;
  double res = determinant(&A);
  fail_if(!(fabs(res - 21.563998) < ACCURACY));
  double res1 = determinant(&C);
  fail_if(!(fabs(res1 - 2.32443) < ACCURACY));
  determinant(&B);
  double res2 = determinant(&D);
  fail_if(!(fabs(res2 - 36.7429) < ACCURACY));
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(determ_2) {
  matrix_t d = create_matrix(4, 4);
  d.matrix[0][0] = 2;
  d.matrix[0][1] = 5;
  d.matrix[0][2] = 8;
  d.matrix[0][3] = 10;
  d.matrix[1][0] = 2;
  d.matrix[1][1] = 4;
  d.matrix[1][2] = 7;
  d.matrix[1][3] = 6;
  d.matrix[2][0] = 5;
  d.matrix[2][1] = 1;
  d.matrix[2][2] = 2;
  d.matrix[2][3] = 3;
  d.matrix[3][0] = 5;
  d.matrix[3][1] = 8;
  d.matrix[3][2] = 9;
  d.matrix[3][3] = 0;
  double det = determinant(&d);
  fail_if(!(fabs(det - -403.0) < ACCURACY));
  // ck_assert_float_eq(det, -403.0);
  matrix_t a = create_matrix(3, 3);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;
  a.matrix[1][2] = 6;
  a.matrix[2][0] = 7;
  a.matrix[2][1] = 8;
  a.matrix[2][2] = 9;
  det = determinant(&a);
  fail_if(!(fabs(det - 0.0) < ACCURACY));
  // ck_assert_float_eq(det, 0.0);
  remove_matrix(&a);
  a.matrix_type = INCORRECT_MATRIX;
  det = determinant(&a);
  ck_assert_msg(isnan(det), "determinant is nan");
  remove_matrix(&d);
}
END_TEST

START_TEST(inverse_1) {
  matrix_t A, C;
  A = create_matrix(3, 3);
  C = create_matrix(3, 3);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  C.matrix_type = 0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  A.matrix_type = 0;
  matrix_t B = inverse_matrix(&A);
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(inverse_2) {
  matrix_t A, B, C, D, E, F, G;
  A = create_matrix(3, 3);
  C = create_matrix(3, 3);
  D = create_matrix(2, 3);
  F = create_matrix(2, 2);
  C.matrix[0][0] = 44300.0 / 367429.0;
  C.matrix[0][1] = -236300.0 / 367429.0;
  C.matrix[0][2] = 200360.0 / 367429.0;
  C.matrix[1][0] = 20600.0 / 367429.0;
  C.matrix[1][1] = 56000.0 / 367429.0;
  C.matrix[1][2] = -156483.0 / 367429.0;
  C.matrix[2][0] = 30900.0 / 367429.0;
  C.matrix[2][1] = 84000.0 / 367429.0;
  C.matrix[2][2] = -51010.0 / 367429.0;
  C.matrix_type = 0;
  A.matrix[0][0] = 2.8;
  A.matrix[0][1] = 1.3;
  A.matrix[0][2] = 7.01;
  A.matrix[1][0] = -1.03;
  A.matrix[1][1] = -2.3;
  A.matrix[1][2] = 3.01;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = -3;
  A.matrix[2][2] = 2;
  A.matrix_type = 0;
  B = inverse_matrix(&A);
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  E = inverse_matrix(&D);
  ck_assert_int_eq(E.matrix_type, 1);
  G = inverse_matrix(&F);
  ck_assert_int_eq(G.matrix_type, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
  remove_matrix(&F);
  remove_matrix(&G);
}
END_TEST

START_TEST(inverse_3) {
  matrix_t res = create_matrix(3, 3);
  res.matrix[0][0] = 1;
  res.matrix[0][1] = -2;
  res.matrix[0][2] = 1;
  res.matrix[1][0] = -2;
  res.matrix[1][1] = 2;
  res.matrix[1][2] = -0.5;
  res.matrix[2][0] = 1;
  res.matrix[2][1] = -0.5;
  res.matrix[2][2] = 0;
  res.matrix_type = 0;

  matrix_t a = create_matrix(3, 3);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 4;
  a.matrix[1][0] = 2;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 6;
  a.matrix[2][0] = 4;
  a.matrix[2][1] = 6;
  a.matrix[2][2] = 8;
  a.matrix_type = 0;

  matrix_t a_obr = inverse_matrix(&a);

  ck_assert_int_eq(eq_matrix(&res, &a_obr), SUCCESS);
  ck_assert_int_eq(a_obr.matrix_type, CORRECT_MATRIX);
  remove_matrix(&a_obr);

  a.matrix_type = INCORRECT_MATRIX;
  a_obr = inverse_matrix(&a);
  ck_assert_int_eq(a_obr.matrix_type, INCORRECT_MATRIX);

  remove_matrix(&a);
  remove_matrix(&res);
  remove_matrix(&a_obr);
}
END_TEST

START_TEST(eq_matrix_1) {
  matrix_t matrix1 = create_matrix(3, 1);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  int result = eq_matrix(&matrix1, &matrix2);
  fail_if(result != 0);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_matrix_2) {
  matrix_t matrix1 = create_matrix(0, 0);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix2.matrix_type = CORRECT_MATRIX;
  int result = eq_matrix(&matrix1, &matrix2);
  fail_if(result != 0);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_matrix_3) {
  matrix_t matrix1 = create_matrix(2, 3);
  matrix_t matrix2 = create_matrix(2, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  int result = eq_matrix(&matrix1, &matrix2);
  fail_if(result != 0);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = create_matrix(3, 3);
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = 10.0;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = sum_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t matrix1 = create_matrix(3, 1);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = sum_matrix(&matrix1, &matrix2);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t matrix1 = create_matrix(2, 3);
  matrix_t matrix2 = create_matrix(2, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = create_matrix(2, 3);
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = 7;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = sum_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t matrix1 = create_matrix(2, 2);
  matrix_t matrix2 = create_matrix(2, 2);
  matrix1.matrix[0][0] = 0.3148823;
  matrix1.matrix[0][1] = 0.2274032;
  matrix1.matrix[1][0] = -0.0338093;
  matrix1.matrix[1][1] = 1.7671095;
  matrix2.matrix[0][0] = -0.1904982;
  matrix2.matrix[0][1] = 2.2972714;
  matrix2.matrix[1][0] = 0.2396589;
  matrix2.matrix[1][1] = 1.9473702;
  matrix_t expected = create_matrix(2, 2);
  expected.matrix[0][0] = 0.1243841;
  expected.matrix[0][1] = 2.5246746;
  expected.matrix[1][0] = 0.2058496;
  expected.matrix[1][1] = 3.7144797;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = sum_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_5) {
  matrix_t matrix1 = create_matrix(0, 0);
  matrix_t matrix2 = create_matrix(2, 2);
  matrix2.matrix[0][0] = -0.1904982;
  matrix2.matrix[0][1] = 2.2972714;
  matrix2.matrix[1][0] = 0.2396589;
  matrix2.matrix[1][1] = 1.9473702;
  matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = sum_matrix(&matrix1, &matrix2);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_6) {
  matrix_t matrix1 = create_matrix(3, 3);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
      matrix2.matrix[i][j] = -1 * (i * matrix1.columns + j + 1);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = sum_matrix(&matrix1, &matrix2);
  fail_if(result.matrix_type != ZERO_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = create_matrix(3, 3);
  int temp = -10;
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = (temp += 2);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = sub_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t matrix1 = create_matrix(3, 2);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = sub_matrix(&matrix1, &matrix2);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t matrix1 = create_matrix(3, 1);
  matrix_t matrix2 = create_matrix(3, 1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = create_matrix(3, 1);
  int temp = -4;
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = (temp += 2);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = sub_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t matrix1 = create_matrix(2, 2);
  matrix_t matrix2 = create_matrix(2, 2);
  matrix1.matrix[0][0] = 0.3879963;
  matrix1.matrix[0][1] = -0.9465799;
  matrix1.matrix[1][0] = 2.8311106;
  matrix1.matrix[1][1] = 2.4766419;
  matrix2.matrix[0][0] = 2.9210337;
  matrix2.matrix[0][1] = 1.8139900;
  matrix2.matrix[1][0] = 1.7304636;
  matrix2.matrix[1][1] = 1.9015551;
  matrix_t expected = create_matrix(2, 2);
  expected.matrix[0][0] = -2.5330374;
  expected.matrix[0][1] = -2.7605699;
  expected.matrix[1][0] = 1.100647;
  expected.matrix[1][1] = 0.5750868;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = sub_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_5) {
  matrix_t matrix1 = create_matrix(0, 0);
  matrix_t matrix2 = create_matrix(2, 2);
  matrix2.matrix[0][0] = -0.1904982;
  matrix2.matrix[0][1] = 2.2972714;
  matrix2.matrix[1][0] = 0.2396589;
  matrix2.matrix[1][1] = 1.9473702;
  matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = sub_matrix(&matrix1, &matrix2);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  double number = 2;
  matrix_t expected = create_matrix(3, 3);
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = (i * matrix1.columns + j + 1) * number;
    }
  }
  expected.matrix_type = CORRECT_MATRIX;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_number(&matrix1, number);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t matrix1 = create_matrix(2, 3);
  matrix1.matrix[0][0] = 0.4244828;
  matrix1.matrix[0][1] = 0.2825884;
  matrix1.matrix[0][2] = -2.5368773;
  matrix1.matrix[1][0] = -1.2964430;
  matrix1.matrix[1][1] = 2.6818946;
  matrix1.matrix[1][2] = 2.6017167;
  double number = 2.528973;
  matrix_t expected = create_matrix(2, 3);
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = matrix1.matrix[i][j] * number;
    }
  }
  expected.matrix_type = CORRECT_MATRIX;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_number(&matrix1, number);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t matrix1 = create_matrix(0, 0);
  double number = 2.528973;
  matrix_t result = mult_number(&matrix1, number);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_4) {
  matrix_t matrix1 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  double number = NAN;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_number(&matrix1, number);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = create_matrix(3, 3);
  expected.matrix[0][0] = 30;
  expected.matrix[0][1] = 24;
  expected.matrix[0][2] = 18;
  expected.matrix[1][0] = 84;
  expected.matrix[1][1] = 69;
  expected.matrix[1][2] = 54;
  expected.matrix[2][0] = 138;
  expected.matrix[2][1] = 114;
  expected.matrix[2][2] = 90;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t matrix1 = create_matrix(3, 1);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_matrix(&matrix1, &matrix2);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t matrix1 = create_matrix(2, 3);
  matrix_t matrix2 = create_matrix(3, 1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = create_matrix(2, 1);
  expected.matrix[0][0] = 10;
  expected.matrix[1][0] = 28;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t matrix1 = create_matrix(2, 2);
  matrix_t matrix2 = create_matrix(2, 2);
  matrix1.matrix[0][0] = 0.4800344;
  matrix1.matrix[0][1] = -2.0621914;
  matrix1.matrix[1][0] = 2.7496997;
  matrix1.matrix[1][1] = 2.2021934;
  matrix2.matrix[0][0] = -1.7362543;
  matrix2.matrix[0][1] = 2.7740213;
  matrix2.matrix[1][0] = 2.9751503;
  matrix2.matrix[1][1] = -0.6493745;
  matrix_t expected = create_matrix(2, 2);
  expected.matrix[0][0] = -6.96879115351534;
  expected.matrix[0][1] = 2.67076015961202;
  expected.matrix[1][0] = 1.77767842683431;
  expected.matrix[1][1] = 6.19767729837531;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix2.matrix_type = CORRECT_MATRIX;
  expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_matrix(&matrix1, &matrix2);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_5) {
  matrix_t matrix1 = create_matrix(0, 0);
  matrix_t matrix2 = create_matrix(3, 3);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = mult_matrix(&matrix1, &matrix2);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix_t expected = create_matrix(3, 3);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 7;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 6;
  expected.matrix[2][2] = 9;
  expected.matrix_type = CORRECT_MATRIX;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = transpose(&matrix1);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t matrix1 = create_matrix(3, 1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix_t expected = create_matrix(1, 3);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix_type = CORRECT_MATRIX;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = transpose(&matrix1);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t matrix1 = create_matrix(2, 2);
  matrix1.matrix[0][0] = 0.5529605;
  matrix1.matrix[0][1] = -0.3930814;
  matrix1.matrix[1][0] = -0.5199081;
  matrix1.matrix[1][1] = -2.0958774;
  matrix_t expected = create_matrix(2, 2);
  expected.matrix[0][0] = 0.5529605;
  expected.matrix[0][1] = -0.5199081;
  expected.matrix[1][0] = -0.3930814;
  expected.matrix[1][1] = -2.0958774;
  expected.matrix_type = CORRECT_MATRIX;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = transpose(&matrix1);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(transpose_4) {
  matrix_t matrix1 = create_matrix(0, 0);
  matrix_t result = transpose(&matrix1);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix_t expected = create_matrix(3, 3);
  expected.matrix[0][0] = -3;
  expected.matrix[0][1] = 6;
  expected.matrix[0][2] = -3;
  expected.matrix[1][0] = 6;
  expected.matrix[1][1] = -12;
  expected.matrix[1][2] = 6;
  expected.matrix[2][0] = -3;
  expected.matrix[2][1] = 6;
  expected.matrix[2][2] = -3;
  expected.matrix_type = CORRECT_MATRIX;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = calc_complements(&matrix1);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t matrix1 = create_matrix(2, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = calc_complements(&matrix1);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t matrix1 = create_matrix(1, 1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 6;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = calc_complements(&matrix1);
  fail_if(!(result.matrix_type != INCORRECT_MATRIX));
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t matrix1 = create_matrix(0, 0);
  matrix_t result = calc_complements(&matrix1);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_5) {
  matrix_t matrix1 = create_matrix(3, 3);
  matrix1.matrix[0][0] = 0.5885548;
  matrix1.matrix[0][1] = -2.1592210;
  matrix1.matrix[0][2] = -2.0269028;
  matrix1.matrix[1][0] = 1.8449226;
  matrix1.matrix[1][1] = -0.3857403;
  matrix1.matrix[1][2] = 2.8620989;
  matrix1.matrix[2][0] = 1.2957987;
  matrix1.matrix[2][1] = -1.5112104;
  matrix1.matrix[2][2] = -0.9130192;
  matrix_t expected = create_matrix(3, 3);
  expected.matrix[0][0] = 4.6774219;
  expected.matrix[0][1] = 5.3931538;
  expected.matrix[0][2] = -2.2882244;
  expected.matrix[1][0] = 1.0916663;
  expected.matrix[1][1] = 2.0890961;
  expected.matrix[1][2] = -1.9084856;
  expected.matrix[2][0] = -6.9617621;
  expected.matrix[2][1] = -5.4239808;
  expected.matrix[2][2] = 3.7565663;
  expected.matrix_type = CORRECT_MATRIX;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = calc_complements(&matrix1);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(determinant_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  double expected = 0.0;
  double result = determinant(&matrix1);
  fail_if(result != expected);
  remove_matrix(&matrix1);
}
END_TEST

START_TEST(determinant_2) {
  matrix_t matrix1 = create_matrix(1, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  double result = determinant(&matrix1);
  fail_if(result == result);
  remove_matrix(&matrix1);
}
END_TEST

START_TEST(determinant_3) {
  matrix_t matrix1 = create_matrix(1, 1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  double expected = matrix1.matrix[0][0];
  double result = determinant(&matrix1);
  fail_if(result != expected);
  remove_matrix(&matrix1);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t matrix1 = create_matrix(0, 0);
  double result = determinant(&matrix1);
  fail_if(result == result);
  remove_matrix(&matrix1);
}
END_TEST

START_TEST(determinant_5) {
  matrix_t s = create_matrix(4, 4);
  s.matrix[0][0] = 1;
  s.matrix[0][1] = 1;
  s.matrix[0][2] = 3, s.matrix[0][3] = 3;
  s.matrix[1][0] = 1;
  s.matrix[1][1] = 0;
  s.matrix[1][2] = 9, s.matrix[1][3] = 8;
  s.matrix[2][0] = 2;
  s.matrix[2][1] = 0;
  s.matrix[2][2] = 7, s.matrix[2][3] = 1;
  s.matrix[3][0] = 4;
  s.matrix[3][1] = 0;
  s.matrix[3][2] = 2, s.matrix[3][3] = 1;
  double result = determinant(&s);
  fail_if(!(result == 169));
  remove_matrix(&s);
}
END_TEST

START_TEST(determinant_6) {
  matrix_t s = create_matrix(4, 4);
  s.matrix[0][0] = 1;
  s.matrix[0][1] = 0;
  s.matrix[0][2] = 3, s.matrix[0][3] = 3;
  s.matrix[1][0] = 1;
  s.matrix[1][1] = 0;
  s.matrix[1][2] = 9, s.matrix[1][3] = 8;
  s.matrix[2][0] = 2;
  s.matrix[2][1] = 0;
  s.matrix[2][2] = 7, s.matrix[2][3] = 1;
  s.matrix[3][0] = 4;
  s.matrix[3][1] = 0;
  s.matrix[3][2] = 2, s.matrix[3][3] = 1;
  double result = determinant(&s);
  fail_if(!(result == 0));
  remove_matrix(&s);
}
END_TEST

START_TEST(determinant_7) {
  matrix_t s = create_matrix(4, 4);
  s.matrix[0][0] = 1;
  s.matrix[0][1] = 0;
  s.matrix[0][2] = NAN, s.matrix[0][3] = 3;
  s.matrix[1][0] = 1;
  s.matrix[1][1] = 0;
  s.matrix[1][2] = 9, s.matrix[1][3] = 8;
  s.matrix[2][0] = 2;
  s.matrix[2][1] = 0;
  s.matrix[2][2] = 7, s.matrix[2][3] = 1;
  s.matrix[3][0] = 4;
  s.matrix[3][1] = 0;
  s.matrix[3][2] = 2, s.matrix[3][3] = 1;
  double result = determinant(&s);
  fail_if(!(result != result));
  remove_matrix(&s);
}
END_TEST

START_TEST(determinant_8) {
  matrix_t s;
  s.matrix = NULL;
  s.columns = 0;
  s.rows = 0;
  s.matrix_type = INCORRECT_MATRIX;
  double result = determinant(&s);
  fail_if(!(result != result));
  remove_matrix(&s);
}
END_TEST

START_TEST(inverse_matrix_1) {
  matrix_t matrix1 = create_matrix(3, 3);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = inverse_matrix(&matrix1);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_2) {
  matrix_t matrix1 = create_matrix(3, 3);
  matrix1.matrix[0][0] = 0.6548129;
  matrix1.matrix[0][1] = 1.4396934;
  matrix1.matrix[0][2] = -1.0722451;
  matrix1.matrix[1][0] = 2.7769395;
  matrix1.matrix[1][1] = -1.9783084;
  matrix1.matrix[1][2] = 2.5705703;
  matrix1.matrix[2][0] = -2.4244804;
  matrix1.matrix[2][1] = -2.2425174;
  matrix1.matrix[2][2] = -2.0103526;
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = inverse_matrix(&matrix1);
  matrix_t checker = mult_matrix(&result, &matrix1);
  fail_if(checker.matrix_type != IDENTITY_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
  remove_matrix(&checker);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t matrix1 = create_matrix(1, 6);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = inverse_matrix(&matrix1);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t matrix1 = create_matrix(0, 0);
  matrix_t result = inverse_matrix(&matrix1);
  fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

Suite *matrix_suite(void) {
  Suite *suite;
  TCase *getCase;

  suite = suite_create("Matrix");
  getCase = tcase_create("core");

  tcase_add_test(getCase, create_1);
  tcase_add_test(getCase, create_2);
  tcase_add_test(getCase, create_3);
  tcase_add_test(getCase, rem_1);
  tcase_add_test(getCase, eq_1);
  tcase_add_test(getCase, eq_2);
  tcase_add_test(getCase, sum_1);
  tcase_add_test(getCase, sum_2);
  tcase_add_test(getCase, sub_1);
  tcase_add_test(getCase, sub_2);
  tcase_add_test(getCase, sub_3);
  tcase_add_test(getCase, mult_num_1);
  tcase_add_test(getCase, mult_num_2);
  tcase_add_test(getCase, mult_m_1);
  tcase_add_test(getCase, mult_m_2);
  tcase_add_test(getCase, trans_1);
  tcase_add_test(getCase, trans_2);
  tcase_add_test(getCase, calc_compl_1);
  tcase_add_test(getCase, calc_compl_2);
  tcase_add_test(getCase, determ_1);
  tcase_add_test(getCase, determ_2);
  tcase_add_test(getCase, inverse_1);
  tcase_add_test(getCase, inverse_2);
  tcase_add_test(getCase, inverse_3);

  tcase_add_test(getCase, eq_matrix_1);
  tcase_add_test(getCase, eq_matrix_2);
  tcase_add_test(getCase, eq_matrix_3);
  tcase_add_test(getCase, sum_matrix_1);
  tcase_add_test(getCase, sum_matrix_2);
  tcase_add_test(getCase, sum_matrix_3);
  tcase_add_test(getCase, sum_matrix_4);
  tcase_add_test(getCase, sum_matrix_5);
  tcase_add_test(getCase, sum_matrix_6);
  tcase_add_test(getCase, sub_matrix_1);
  tcase_add_test(getCase, sub_matrix_2);
  tcase_add_test(getCase, sub_matrix_3);
  tcase_add_test(getCase, sub_matrix_4);
  tcase_add_test(getCase, sub_matrix_5);
  tcase_add_test(getCase, mult_number_1);
  tcase_add_test(getCase, mult_number_2);
  tcase_add_test(getCase, mult_number_3);
  tcase_add_test(getCase, mult_number_4);
  tcase_add_test(getCase, mult_matrix_1);
  tcase_add_test(getCase, mult_matrix_2);
  tcase_add_test(getCase, mult_matrix_3);
  tcase_add_test(getCase, mult_matrix_4);
  tcase_add_test(getCase, mult_matrix_5);
  tcase_add_test(getCase, transpose_1);
  tcase_add_test(getCase, transpose_2);
  tcase_add_test(getCase, transpose_3);
  tcase_add_test(getCase, transpose_4);
  tcase_add_test(getCase, calc_complements_1);
  tcase_add_test(getCase, calc_complements_2);
  tcase_add_test(getCase, calc_complements_3);
  tcase_add_test(getCase, calc_complements_4);
  tcase_add_test(getCase, calc_complements_5);
  tcase_add_test(getCase, determinant_1);
  tcase_add_test(getCase, determinant_2);
  tcase_add_test(getCase, determinant_3);
  tcase_add_test(getCase, determinant_4);
  tcase_add_test(getCase, determinant_5);
  tcase_add_test(getCase, determinant_6);
  tcase_add_test(getCase, determinant_7);
  tcase_add_test(getCase, determinant_8);
  tcase_add_test(getCase, inverse_matrix_1);
  tcase_add_test(getCase, inverse_matrix_2);
  tcase_add_test(getCase, inverse_matrix_3);
  tcase_add_test(getCase, inverse_matrix_4);

  suite_add_tcase(suite, getCase);

  return suite;
}

int main(void) {
  int amountOfFailed = 0;
  SRunner *runner;
  Suite *suite;

  suite = matrix_suite();
  runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  amountOfFailed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (amountOfFailed == 0) ? 0 : 1;
}
