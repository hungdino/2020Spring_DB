SELECT
A.v AS version,
SUM(A.w) AS win_cnt,
COUNT(*) - SUM(A.w) AS lose_cnt,
SUM(A.w)/COUNT(*) AS win_ratio
FROM(
SELECT
SUBSTRING_INDEX(version, ".", 2) AS v, win AS w,
champion_name AS c_n, match_id AS m_i, player AS p
FROM match_info
NATURAL JOIN participant
NATURAL JOIN stat
NATURAL JOIN champ
) AS A LEFT JOIN (
SELECT
SUBSTRING_INDEX(version, ".", 2) AS v, win AS w,
champion_name AS c_n, match_id AS m_i, player AS p
FROM match_info
NATURAL JOIN participant
NATURAL JOIN stat
NATURAL JOIN champ
) AS B 
ON (A.m_i = B.m_i AND A.w = B.w AND B.c_n IN ("Lee Sin","Teemo"))
WHERE A.c_n = "Lee Sin" AND B.c_n = "Teemo"
GROUP BY version
ORDER BY version;
