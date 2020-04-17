SELECT A.pos AS position, A.c_n AS champion_name
FROM
(
SELECT position pos, champion_name c_n,
MAX((kills+assists)/deaths) kda
FROM participant P
NATURAL JOIN stat
NATURAL JOIN champ
WHERE deaths > 0 AND position NOT IN ("NONE", "SOLO", "DUO")
GROUP BY pos, c_n
) AS A 
LEFT JOIN
(
SELECT position pos, champion_name c_n,
MAX((kills+assists)/deaths) kda
FROM participant P
NATURAL JOIN stat
NATURAL JOIN champ
WHERE deaths > 0 AND position NOT IN ("NONE", "SOLO", "DUO")
GROUP BY pos, c_n
) AS B
ON A.pos = B.pos AND A.kda < B.kda
WHERE B.kda is NULL AND A.pos NOT IN ("NONE", "SOLO", "DUO")
ORDER BY A.pos