CREATE TABLE  my7sql SELECT pos position, champion_name, kda
FROM
	(SELECT A.pos pos, A.c_i c_i, A.kda kda
	FROM
		(SELECT
		position pos,
		champion_id c_i,
		(SUM(kills)+SUM(assists))/SUM(deaths) kda
		FROM participant P JOIN stat S 
		ON (P.player_id = S.player_id AND P.position NOT IN ("NONE", "SOLO", "DUO"))
		GROUP BY pos, c_i ) AS A 
	LEFT JOIN
		(SELECT
		position pos,
		champion_id c_i,
		(SUM(kills)+SUM(assists))/SUM(deaths) kda
		FROM participant P JOIN stat S 
		ON (P.player_id = S.player_id AND P.position NOT IN ("NONE", "SOLO", "DUO"))
		GROUP BY pos, c_i ) AS B
	ON (A.pos = B.pos AND A.kda < B.kda)
	WHERE B.kda is NULL
	) AS RESULT JOIN champ ON (RESULT.c_i = champ.champion_id)
ORDER BY position ASC;


