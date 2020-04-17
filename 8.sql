
SELECT champion_name FROM champ
WHERE champion_name NOT IN
(
SELECT DISTINCT champion_id
FROM teamban 
NATURAL JOIN match_info
WHERE SUBSTRING_INDEX(version, ".", 2) = "7.7"
)