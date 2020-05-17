SELECT
match_id AS match_id,
SEC_TO_TIME(time) AS time
FROM(SELECT
match_id AS match_id,
duration AS time
FROM match_info AS m_info
ORDER BY time DESC
LIMIT 5) AS id_second_table
;