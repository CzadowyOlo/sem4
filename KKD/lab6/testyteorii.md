   x_n: =   10, 14, 10, 12, 14, 8, 14, 12, 10, 8, 10, 12, 18 // ciąg wartości do zakodowania (13 bitów)
    

    y(n): 10, 12, 12, 11, 13, 11, 11, 13, 11, 10, 9, 11, 15  //ciąg wartości filtra dolnoprzepustowego
    z(n):  0,  2, -2,  1,  1, -3,  3, -1, -1, -1,  1, 1,  3  //ciąg wartości filtra górnooprzepustowego

    kodowac roznicowo y(n):
    10, 2, 0, -1, 

            0   1   2   3   4   5   6
    y2(n): 10, 12, 13, 11, 11, 9,  15
    z2(n):  _, -2,  1,  3, -1,  1,  3   // w sumie 13 bitów

    x_2n   = y_2n + z_2n
    x_2n-1 = y_2n - z_2n

    x_2n   = y2_n + z2_n
    x_2n-1 = y2_n - z2_n


            0   1   2   3   4   5
   x_n: =   10, 14, 10, 12, 14, 8, 14, 12, 10, 8, 10, 12, 18 // odkodowany ciąg x (13 bitów)

    x[1] = ( x_2n-1 = y2_n - z2_n ) = 14
    x[2] = ( x_2n   = y2_n + z2_n ) = 10

