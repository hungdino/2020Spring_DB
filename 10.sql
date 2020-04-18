SELECT *
FROM(SELECT
A.c_n self_champ_name,
SUM(A.w)/COUNT(A.w) win_ratio,
SUM(A.ka)/SUM(A.d) self_kda,
AVG(A.g) self_avg_gold,
B.c_n enemy_champ_name,
SUM(B.ka)/SUM(B.d) enemy_kda,
AVG(B.g) enemy_avg_gold,
COUNT(*) battle_record
FROM(
	SELECT
	champion_name c_n,
	win w,
	kills+assists ka,
	deaths d,
	goldearned g,
	match_id m_i 
	FROM participant NATURAL JOIN stat NATURAL JOIN champ
	WHERE position = "TOP"
) AS A LEFT JOIN (
	SELECT
	champion_name c_n,
	win w,
	kills+assists ka,
	deaths d,
	goldearned g,
	match_id m_i 
	FROM participant NATURAL JOIN stat NATURAL JOIN champ
	WHERE position = "TOP"
) AS B ON (A.m_i = B.m_i AND B.c_n = "Renekton")
WHERE B.c_n is NOT NULL
GROUP BY A.c_n) AS Result
WHERE battle_record > 100
ORDER BY win_ratio DESC
LIMIT 5