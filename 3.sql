SELECT
champion_name AS champion_name,
cnt AS cnt
FROM(
SELECT 
champion_id AS champion_id,
COUNT(*) AS cnt
FROM participant AS p
WHERE position = "JUNGLE"
GROUP BY champion_id
ORDER BY cnt DESC
LIMIT 3
) AS id_cnt
INNER JOIN champ ON (champ.champion_id = id_cnt.champion_id )
;