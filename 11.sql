SELECT
P.ss1 ss1,
P.ss2 ss2,
SUM(S.win) win_cnt,
COUNT(S.win) matches,
SUM(S.win)/COUNT(S.win) win_ratio
FROM participant P
JOIN stat S ON (P.player_id = S.player_id)
JOIN 
WHERE 	(
		ss1 in ("Flash", "Ignite") AND
		ss2 in ("Flash", "Ignite") AND
		position = "TOP"
		)
GROUP BY ss1, ss2

SELECT
P.ss1 ss1,
P.ss2 ss2,
SUM(S.win) win_cnt,
COUNT(S.win) matches,
SUM(S.win)/COUNT(S.win) win_ratio
FROM participant P JOIN stat S ON (P.player_id = S.player_id)
WHERE 	(
		position = "TOP"
		)
GROUP BY ss1, ss2
ORDER BY win_ratio DESC

閃現+傳送 >> 其他
