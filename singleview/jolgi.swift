typealias Nalja = (Int, Int, Int, Int)
typealias JolgiDict = [Int:[Nalja]]

// Jolgi from 1940
let Jolgi: JolgiDict = [
  1940 : [(1, 6, 20, 24), (2,5,8,8), (3,6,2,24),(4,5,7,35), (5, 6, 1, 16), (6, 6, 5, 44),
          (7, 7, 16, 8), (8, 8, 1, 52), (9,8,4,29), (10,8,19,42), (11,7,22,27), (12,7,14,58)],
  1941 : [(1, 6, 2, 4), (2,4,13,50), (3,6,8,10),(4,5,13,25), (5, 6, 7, 10), (6, 6, 11, 39),
          (7, 7, 22, 3), (8, 8, 7, 46), (9,8,10,24), (10,9,1,38), (11,8,4,24), (12,7,20,56)],
  1942 : [(1, 6, 8, 2), (2,4,19,49), (3,6,14,9),(4,5,19,24), (5, 6, 13, 7), (6, 6, 17, 33),
          (7, 8, 3, 52), (8, 8, 13, 30), (9,8,16,6), (10,9,7,22), (11,8,10,11), (12,8,2,47)],
  1943 : [(1, 6, 13, 55), (2,5,1,40), (3,6,19,59),(4,6,1,11), (5, 6, 18, 53), (6, 6, 23, 19),
          (7, 8, 9, 39), (8, 8, 19, 19), (9,8,21,55), (10,9,13,11), (11,8,15,59), (12,8,8,33)],
  1944 : [(1, 6, 19, 39), (2,5,7,23), (3,6,1,40),(4,5,6,54), (5, 6, 0, 40), (6, 6, 5, 11),
          (7, 7, 15, 36), (8, 8, 1, 19), (9,8,3,56), (10,8,19,9), (11,7,21,55), (12,7,14,28)],
  1945 : [(1, 6, 1, 34), (2,4,13,19), (3,6,7,38),(4,5,12,52), (5, 6, 6, 37), (6, 6, 11, 5),
          (7, 7, 21, 27), (8, 8, 7, 5), (9,8,9,38), (10,9,0,49), (11,8,3,34), (12,7,20,8)],
  1946 : [(1, 6, 7, 16), (2,4,19,4), (3,6,13,25),(4,5,18,39), (5, 6, 12, 22), (6, 6, 16, 49),
          (7, 8, 3, 11), (8, 8, 12, 52), (9,8,15,27), (10,9,6,41), (11,8,9,27), (12,8,2,0)],
  1947 : [(1, 6, 13, 6), (2,5,0,50), (3,6,19,8),(4,6,0,20), (5, 6, 18, 3), (6, 6, 22, 31),
          (7, 8, 8, 56), (8, 8, 18, 41), (9,8,21,21), (10,9,12,37), (11,8,15,24), (12,8,7,56)],
  1948 : [(1, 6, 19, 0), (2,5,6,42), (3,6,0,58),(4,5,6,9), (5, 5, 23, 52), (6, 6, 4, 20),
          (7, 7, 14, 44), (8, 8, 0, 26), (9,8,3,5), (10,8,18,20), (11,7,21,7), (12,7,13,38)],
  1949 : [(1, 6, 0, 41), (2,4,12,23), (3,6,6,39),(4,5,11,52), (5, 6, 5, 37), (6, 6, 10, 7),
          (7, 7, 20, 32), (8, 8, 6, 15), (9,8,8,54), (10,9,0,11), (11,8,3,0), (12,7,19,33)],
  1950 : [(1, 6, 6, 39), (2,4,18,21), (3,6,12,35),(4,5,17,44), (5, 6, 11, 25), (6, 6, 15, 51),
          (7, 8, 2, 13), (8, 8, 11, 55), (9,8,14,34), (10,9,5,52), (11,8,8,44), (12,8,1,22)],
  1951 : [(1, 6, 12, 30), (2,5,0,13), (3,6,18,27),(4,5,23,33), (5, 6, 17, 9), (6, 6, 21, 33),
          (7, 8, 7, 54), (8, 8, 17, 37), (9,8,20,18), (10,9,11,36), (11,8,14,27), (12,8,7,2)],
  1952 : [(1, 6, 18, 10), (2,5,5,53), (3,6,0,7),(4,5,5,15), (5, 5, 22, 54), (6, 6, 3, 20),
          (7, 7, 13, 45), (8, 7, 23, 31), (9,8,2,14), (10,8,17,32), (11,7,20,22), (12,7,12,56)],
  1953 : [(1, 6, 0, 2), (2,4,11,46), (3,6,6,2),(4,5,11,13), (5, 6, 4, 52), (6, 6, 9, 16),
          (7, 7, 19, 35), (8, 8, 5, 15), (9,8,7,53), (10,8,23,10), (11,8,2,1), (12,8,18,37)],
  1954 : [(1, 6, 5, 45), (2,4,17,31), (3,6,11,49),(4,5,16,59), (5, 6, 10, 38), (6, 6, 15, 1),
          (7, 8, 1, 19), (8, 8, 10, 59), (9,8,13,38), (10,9,4,57), (11,8,7,51), (12,8,0,29)],
  1955 : [(1, 6, 11, 36), (2,4,23,18), (3,6,17,31),(4,5,22,39), (5, 6, 16, 18), (6, 6, 20, 43),
          (7, 8, 7, 6), (8, 8, 16, 50), (9,8,19,32), (10,9,10,52), (11,8,13,45), (12,8,6,23)],
  1956 : [(1, 6, 17, 30), (2,5,5,12), (3,5,23,24),(4,5,4,31), (5, 5, 22, 10), (6, 6, 2, 36),
          (7, 7, 12, 58), (8, 7, 22, 40), (9,8,1,19), (10,8,16,36), (11,7,19,26), (12,7,12,2)],
  1957 : [(1, 5, 23, 10), (2,4,10,55), (3,6,5,10),(4,5,10,19), (5, 6, 3, 58), (6, 6, 8, 25),
          (7, 7, 18, 48), (8, 8, 4, 32), (9,8,7,12), (10,8,12,30), (11,8,1,20), (12,7,17,56)],
  1958 : [(1, 6, 5, 4), (2,4,16,49), (3,6,11,5),(4,5,16,12), (5, 6, 19, 49), (6, 6, 14, 12),
          (7, 8, 0, 33), (8, 8, 10, 17), (9,8,12,59), (10,9,4,19), (11,8,7,12), (12,7,23,50)],
  1959 : [(1, 6, 10, 58), (2,4,22,42), (3,6,16,57),(4,5,22,3), (5, 6, 15, 39), (6, 6, 20, 0),
          (7, 8, 6, 20), (8, 8, 16, 4), (9,8,18,48), (10,9,10,10), (11,8,13,2), (12,8,5,37)],
  1960 : [(1, 6, 16, 42), (2,5,4,23), (3,5,22,36),(4,5,3,44), (5, 5, 21, 23), (6, 6, 1, 49),
          (7, 7, 12, 13), (8, 7, 22, 0), (9,8,0,45), (10,8,16,9), (11,7,19,2), (12,7,11,38)],
  1961 : [(1, 5, 22, 43), (2,4,10,22), (3,6,4,35),(4,5,9,42), (5, 6, 3, 21), (6, 6, 7, 46),
          (7, 7, 18, 7), (8, 8, 3, 48), (9,8,6,29), (10,8,21,51), (11,8,0,46), (12,7,17,26)],
  1962 : [(1, 6, 4, 35), (2,4,16,17), (3,6,10,30),(4,5,15,34), (5, 6, 9, 10), (6, 6, 13, 31),
          (7, 7, 23, 51), (8, 8, 9, 34), (9,8,12,15), (10,9,3,38), (11,8,6,35), (12,7,23,17)],
  1963 : [(1, 6, 10, 26), (2,4,22,8), (3,6,16,17),(4,5,21,19), (5, 6, 14, 52), (6, 6, 19, 14),
          (7, 8, 5, 38), (8, 8, 15, 25), (9,8,18,12), (10,9,9,36), (11,8,12,32), (12,8,5,13)],
  1964 : [(1, 6, 16, 22), (2,5,4,5), (3,5,22,16),(4,5,3,18), (5, 5, 20, 51), (6, 6, 1, 12),
          (7, 7, 11, 32), (8, 7, 21, 16), (9,7,23,59), (10,8,15,22), (11,7,18,15), (12,7,10,53)],
  1965 : [(1, 5, 22, 2), (2,4,9,46), (3,6,4,1),(4,5,9,7), (5, 6, 2, 42), (6, 6, 7, 2),
          (7, 7, 17, 21), (8, 8, 3, 5), (9,8,5,48), (10,8,21,11), (11,8,0,7), (12,7,16,46)],
  1966 : [(1, 6, 3, 54), (2,4,15,38), (3,6,9,51),(4,5,14,57), (5, 6, 8, 30), (6, 6, 12, 50),
          (7, 7, 23, 7), (8, 8, 8, 49), (9,8,11,32), (10,9,2,57), (11,8,5,55), (12,7,22,38)],
  1967 : [(1, 6, 9, 48), (2,4,21,31), (3,6,15,42),(4,5,20,45), (5, 6, 14, 17), (6, 6, 18, 36),
          (7, 8, 4, 53), (8, 8, 14, 35), (9,8,17,18), (10,9,8,41), (11,8,11,37), (12,8,4,18)],
  1968 : [(1, 6, 15, 26), (2,5,3,7), (3,5,21,18),(4,5,2,21), (5, 5, 19, 56), (6, 6, 0, 19),
          (7, 7, 10, 42), (8, 7, 20, 27), (9,7,23,11), (10,8,14,34), (11,7,17,29), (12,7,10,8)],
  1969 : [(1, 5, 21, 17), (2,4,8,59), (3,6,3,11),(4,5,8,15), (5, 6, 1, 50), (6, 6, 6, 12),
          (7, 7, 16, 32), (8, 8, 2, 14), (9,8,4,55), (10,8,20,17), (11,7,23,11), (12,7,15,51)],
  1970 : [(1, 6, 3, 2), (2,4,14,46), (3,6,8,58),(4,5,14,2), (5, 6, 7, 34), (6, 6, 11, 52),
          (7, 7, 22, 11), (8, 8, 7, 54), (9,8,10,38), (10,9,2,2), (11,8,4,58), (12,7,21,37)],
  1971 : [(1, 6, 8, 45), (2,4,20,25), (3,6,14,35),(4,5,19,36), (5, 6, 13, 8), (6, 6, 17, 29),
          (7, 8, 3, 51), (8, 8, 13, 40), (9,8,16,30), (10,9,7,59), (11,8,10,57), (12,8,3,36)],
  1972 : [(1, 6, 14, 42), (2,5,2,20), (3,5,20,28),(4,5,1,59), (5, 5, 19, 1), (6, 5, 23, 22),
          (7, 7, 9, 43), (8, 7, 19, 29), (9,7,22,15), (10,8,13,42), (11,7,16,39), (12,7,9,19)],
  1973 : [(1, 5, 20, 25), (2,4,8,4), (3,6,2,13),(4,5,7,14), (5, 6, 0, 46), (6, 6, 5, 7),
          (7, 7, 15, 27), (8, 8, 1, 13), (9,8,3,59), (10,8,19,27), (11,7,22,28), (12,7,15,10)],
  1974 : [(1, 6, 2, 20), (2,4,14,0), (3,6,8,7),(4,5,13,5), (5, 6, 6, 34), (6, 6, 10, 52),
          (7, 7, 21, 11), (8, 8, 6, 57), (9,8,9,45), (10,9,1,15), (11,8,4,18), (12,7,21,5)],
  1975 : [(1, 6, 8, 18), (2,4,19,59), (3,6,14,6),(4,5,19,2), (5, 6, 12, 27), (6, 6, 16, 42),
          (7, 8, 2, 59), (8, 8, 12, 45), (9,8,15,33), (10,9,7,2), (11,8,10,3), (12,8,2,46)],
  1976 : [(1, 6, 13, 57), (2,5,1,39), (3,5,19,48),(4,5,0,46), (5, 5, 18, 14), (6, 5, 22, 31),
          (7, 7, 8, 51), (8, 7, 18, 38), (9,7,21,28), (10,8,12,58), (11,7,15,59), (12,7,8,41)],
  1977 : [(1, 5, 19, 51), (2,4,7,33), (3,6,1,44),(4,5,6,46), (5, 6, 0, 16), (6, 6, 4, 32),
          (7, 7, 14, 48), (8, 8, 0, 30), (9,8,3,16), (10,8,18,44), (11,7,21,46), (12,7,13,31)],
  1978 : [(1, 6, 1, 43), (2,4,13,27), (3,6,7,38),(4,5,12,39), (5, 6, 6, 9), (6, 6, 10, 23),
          (7, 7, 20, 37), (8, 8, 6, 18), (9,8,9,2), (10,9,0,31), (11,8,3,34), (12,7,20,20)],
  1979 : [(1, 6, 7, 32), (2,4,19,12), (3,6,13,20),(4,5,18,18), (5, 6, 11, 47), (6, 6, 16, 5),
          (7, 8, 2, 25), (8, 8, 12, 11), (9,8,15,0), (10,9,6,30), (11,8,9,33), (12,8,2,18)],
  1980 : [(1, 6, 13, 29), (2,5,1,9), (3,5,19,17),(4,5,0,15), (5, 5, 17, 45), (6, 5, 22, 4),
          (7, 7, 8, 24), (8, 7, 18, 9), (9,7,20,53), (10,8,12,19), (11,7,15,18), (12,7,8,1)],
  1981 : [(1, 5, 19, 13), (2,4,6,55), (3,6,1,5),(4,5,6,5), (5, 5, 23, 35), (6, 6, 3, 53),
          (7, 7, 14, 12), (8, 7, 23, 57), (9,8,2,43), (10,8,18,10), (11,7,21,9), (12,7,13,51)],
  1982 : [(1, 6, 1, 3), (2,4,12,45), (3,6,6,55),(4,5,11,53), (5, 6, 5, 20), (6, 6, 9, 36),
          (7, 7, 19, 55), (8, 8, 5, 42), (9,8,8,32), (10,9,0,2), (11,8,3,4), (12,7,19,48)],
  1983 : [(1, 6, 6, 59), (2,4,18,40), (3,6,12,47),(4,5,17,44), (5, 6, 11, 11), (6, 6, 15, 26),
          (7, 8, 1, 43), (8, 8, 11, 30), (9,8,14,20), (10,9,5,51), (11,8,8,52), (12,8,1,34)],
  1984 : [(1, 6, 12, 41), (2,5,0,19), (3,5,18,25),(4,4,23,22), (5, 5, 16, 51), (6, 5, 21, 9),
          (7, 7, 7, 29), (8, 7, 17, 18), (9,7,20,19), (10,8,11,43), (11,7,14,46), (12,7,7,28)],
  1985 : [(1, 5, 18, 35), (2,4,6,12), (3,6,0,16),(4,5,5,14), (5, 5, 22, 43), (6, 6, 3, 0),
          (7, 7, 13, 19), (8, 7, 23, 4), (9,8,1,53), (10,8,17,25), (11,7,20,29), (12,7,13,16)],
  1986 : [(1, 6, 0, 28), (2,4,12,8), (3,6,6,12),(4,5,11,6), (5, 6, 4, 31), (6, 6, 8, 44),
          (7, 7, 19, 1), (8, 8, 4, 46), (9,8,7,35), (10,8,23,7), (11,8,2,13), (12,7,19,1)],
  1987 : [(1, 6, 6, 13), (2,4,17,52), (3,6,11,54),(4,5,16,44), (5, 6, 10, 6), (6, 6, 14, 19),
          (7, 8, 0, 39), (8, 8, 10, 29), (9,8,13,24), (10,9,5,0), (11,8,8,6), (12,8,0,52)],
  1988 : [(1, 6, 12, 4), (2,4,23,43), (3,5,17,47),(4,4,22,39), (5, 5, 16, 2), (6, 5, 20, 15),
          (7, 7, 6, 33), (8, 7, 16, 20), (9,7,19,12), (10,8,10,45), (11,7,13,49), (12,7,6,34)],
  1989 : [(1, 5, 17, 46), (2,4,5,27), (3,5,23,34),(4,5,4,30), (5, 5, 21, 54), (6, 6, 2, 5),
          (7, 7, 12, 19), (8, 7, 22, 4), (9,8,0,54), (10,8,16,27), (11,7,19,34), (12,7,12,21)],
  1990 : [(1, 5, 23, 34), (2,4,11,14), (3,6,5,19),(4,5,10,34), (5, 6, 3, 35), (6, 6, 7, 46),
          (7, 7, 18, 0), (8, 8, 3, 46), (9,8,6,37), (10,8,22,14), (11,8,1,23), (12,7,18,14)],
  1991 : [(1, 6, 5, 28), (2,4,17,8), (3,6,11,12),(4,5,16,5), (5, 6, 9, 27), (6, 6, 13, 38),
          (7, 7, 23, 53), (8, 8, 9, 37), (9,8,12,27), (10,9,4,1), (11,8,7,8), (12,7,23,56)],
  1992 : [(1, 6, 11, 9), (2,4,22,48), (3,5,16,52),(4,4,21,45), (5, 5, 15, 9), (6, 5, 19, 22),
          (7, 7, 5, 40), (8, 7, 15, 27), (9,7,18,18), (10,8,9,51), (11,7,12,57), (12,7,5,44)],
  1993 : [(1, 5, 16, 57), (2,4,4,37), (3,5,22,43),(4,5,3,37), (5, 5, 21, 2), (6, 6, 1, 15),
          (7, 7, 11, 32), (8, 7, 21, 18), (9,8,0,8), (10,8,15,40), (11,7,18,46), (12,7,11,34)],
  1994 : [(1, 5, 22, 48), (2,4,10,31), (3,6,4,38),(4,5,3,32), (5, 6, 2, 54), (6, 6, 7, 5),
          (7, 7, 17, 19), (8, 8, 3, 4), (9,8,5,55), (10,8,21,29), (11,8,0,36), (12,7,17,23)],
  1995 : [(1, 6, 4, 34), (2,4,16,13), (3,6,10,16),(4,5,15,8), (5, 6, 8, 30), (6, 6, 12, 43),
          (7, 7, 23, 1), (8, 8, 8, 52), (9,8,11,49), (10,9,3,27), (11,8,6,36), (12,7,23,22)],
  1996 : [(1, 6, 10, 31), (2,4,22,8), (3,5,16,10),(4,4,21,2), (5, 5, 14, 26), (6, 5, 18, 41),
          (7, 7, 5, 0), (8, 7, 14, 49), (9,7,17,42), (10,8,9,19), (11,7,12,27), (12,7,5,14)],
  1997 : [(1, 5, 16, 24), (2,4,4,2), (3,5,22,4),(4,5,2,56), (5, 5, 20, 19), (6, 6, 0, 33),
          (7, 7, 10, 49), (8, 7, 20, 36), (9,7,23,29), (10,8,15,5), (11,7,18,15), (12,7,11,5)],
  1998 : [(1, 5, 22, 18), (2,4,9,57), (3,6,3,57),(4,5,8,45), (5, 6, 2, 3), (6, 6, 6, 13),
          (7, 7, 16, 30), (8, 8, 2, 20), (9,8,5,16), (10,8,20,56), (11,8,0,8), (12,7,17,2)],
  1999 : [(1, 6, 4, 17), (2,4,15,57), (3,6,9,58),(4,5,14,45), (5, 6, 8, 1), (6, 6, 12, 9),
          (7, 7, 22, 25), (8, 8, 8, 14), (9,8,11,10), (10,9,2,48), (11,8,5,58), (12,7,22,47)],
  2000 : [(1, 6, 10, 1), (2,4,21,40), (3,5,15,43),(4,4,20,32), (5, 5, 13, 50), (6, 5, 17, 59),
          (7, 7, 4, 14), (8, 7, 14, 3), (9,7,16,59), (10,8,8,38), (11,7,11,48), (12,7,4,37)],
  2001 : [(1, 5, 15, 49), (2,4,3,29), (3,5,21,32),(4,5,2,24), (5, 5, 19, 45), (6, 5, 23, 54),
          (7, 7, 10, 7), (8, 7, 19, 52), (9,7,22,46), (10,8,14,25), (11,7,17,37), (12,7,10,29)],
  2002 : [(1, 5, 21, 43), (2,4,9,24), (3,6,3,28),(4,5,8,18), (5, 6, 1, 37), (6, 6, 5, 45),
          (7, 7, 15, 56), (8, 8, 1, 39), (9,8,4,31), (10,8,20,9), (11,7,23,22), (12,7,16,14)],
  2003 : [(1, 6, 3, 28), (2,4,15,5), (3,6,9,5),(4,5,13,52), (5, 6, 7, 10), (6, 6, 11, 20),
          (7, 7, 21, 36), (8, 8, 7, 24), (9,8,10,20), (10,9,2,0), (11,8,5,13), (12,7,22,5)],
  2004 : [(1, 6, 9, 19), (2,4,20,56), (3,5,14,56),(4,4,19,43), (5, 5, 13, 2), (6, 5, 17, 14),
          (7, 7, 3, 31), (8, 7, 13, 20), (9,7,16,13), (10,8,7,49), (11,7,10,59), (12,7,3,49)],
  2005 : [(1, 6, 9, 19), (2,4,20,56), (3,5,14,56),(4,4,19,43), (5, 5, 13, 2), (6, 5, 17, 14),
          (7, 7, 3, 31), (8, 7, 13, 20), (9,7,16,13), (10,8,7,49), (11,7,10,59), (12,7,3,49)],
  2016 : [(1, 6, 7, 8), (2,4,18,46), (3,5,12,43),(4,4,17,27), (5, 5, 10, 42), (6, 5, 14, 48),
          (7, 7, 1, 3), (8, 7, 10, 53), (9,7,13,51), (10,8,5,33), (11,7,8,48), (12,7,1,41)],
  2017: [(1, 5, 12, 56), (2,4,0,34), (3,5,18,33),(4,4,23,17), (5, 5, 16, 31), (6, 5, 20, 36),
         (7, 7, 6, 51), (8, 7, 16, 40), (9,7,19,38), (10,8,11,22), (11,7,14,38), (12,7,7,32)],
  2018: [(1, 5, 18, 49), (2,4,6,28), (3,6,0,28),(4,5,5,13), (5, 5, 22, 25), (6, 6, 2, 29),
         (7, 7, 12, 42), (8, 7, 22, 30), (9,8,1,30), (10,8,17,15), (11,7,20,32), (12,7,13,26)],
  2019: [(1, 6, 0, 39), (2,4,12,14), (3,6,6,10),(4,5,10,51), (5, 6, 4, 3), (6, 6, 8, 6),
         (7, 7, 18, 20), (8, 8, 4, 13), (9,8,7,17), (10,8,23,5), (11,8,2,24), (12,7,19,18)],
]
