SELECT
win_lose AS win_lose,
COUNT(win_lose) AS cnt
FROM(
SELECT CASE WHEN
win <> 0 THEN "win" ELSE "lose" END AS win_lose
FROM(
SELECT
match_id AS m_id,
win AS win,
SUM(longesttimespentliving)/5 AS team_avg_living_time
FROM stat AS stat
NATURAL JOIN participant
GROUP BY m_id, win) AS team_avg_table
WHERE team_avg_living_time >= 1200) AS win_lose_table
GROUP BY win_lose
;