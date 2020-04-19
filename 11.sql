SELECT SUM(matches) Team_cnt FROM (
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
) AS SS_CNT;


SELECT * FROM(
SELECT
P.ss1 ss1,
P.ss2 ss2,
SUM(S.win) win_cnt,
COUNT(S.win)/362944 used_ratio,
SUM(S.win)/COUNT(S.win) win_ratio
FROM participant P JOIN stat S ON (P.player_id = S.player_id)
WHERE 	(
		position = "TOP"
		)
GROUP BY ss1, ss2) AS SS_Table
WHERE used_ratio > 0.01
ORDER BY used_ratio DESC;


SELECT *
FROM participant P JOIN stat S ON (P.player_id = S.player_id AND P.position = "TOP") AS A
LEFT JOIN (
SELECT *
FROM participant P
JOIN stat S ON (P.player_id = S.player_id AND P.position = "TOP")
) AS B ON (A.match_id = B.match_id AND A.ss1 in ("Flash", "Teleport") AND A.ss2 in ("Flash", "Teleport") AND
		B.ss1 in ("Flash", "Ignite") AND B.ss2 in ("Flash", "Ignite"));
 

SELECT TP_win_cnt, IG_win_cnt, TP_win_cnt/(TP_win_cnt+IG_win_cnt) TP_vs_IG_win_ratio FROM(
SELECT SUM(tp_win) TP_win_cnt, SUM(ig_win) IG_win_cnt FROM(
SELECT 
SUM(A.w) AS tp_win, SUM(B.w) AS ig_win
FROM(
	SELECT
	match_id m_i,
	ss1, ss2,
	win w
	FROM participant NATURAL JOIN stat
	WHERE position = "TOP" AND ss1 in ("Flash", "Teleport") AND ss2 in ("Flash", "Teleport")
) AS A LEFT JOIN (
	SELECT
	match_id m_i,
	ss1, ss2,
	win w
	FROM participant NATURAL JOIN stat
	WHERE position = "TOP" AND ss1 in ("Flash", "Ignite") AND ss2 in ("Flash", "Ignite")
) AS B ON (A.m_i = B.m_i)
WHERE B.m_i is NOT NULL
GROUP BY A.ss1, A.ss2) AS COUNTer) AS Result;