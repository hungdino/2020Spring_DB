SELECT A.pos AS position, A.c_n AS champion_name
FROM(
SELECT pos, champion_name AS c_n, COUNT(*) AS cnt
FROM(
	SELECT champion_id AS c_i, position AS pos FROM match_info MI 
	JOIN participant P ON MI.match_id = P.match_id 
	WHERE MI.duration BETWEEN 2400 AND 3000
	) AS CHA_POS JOIN champ ON (CHA_POS.c_i = champ.champion_id)
GROUP BY pos, champion_name
) AS A LEFT JOIN
(SELECT pos, champion_name AS c_n, COUNT(*) AS cnt
FROM(
	SELECT champion_id AS c_i, position AS pos FROM match_info MI 
	JOIN participant P ON MI.match_id = P.match_id 
	WHERE MI.duration BETWEEN 2400 AND 3000
	) AS CHA_POS JOIN champ ON (CHA_POS.c_i = champ.champion_id)
GROUP BY pos, champion_name) AS B
	ON A.pos = B.pos AND A.cnt < B.cnt
	WHERE B.cnt is NULL AND A.pos NOT IN ("NONE", "SOLO", "DUO")
	ORDER BY position