SELECT COUNT(*) cnt 
FROM (
	select DISTINCT SUBSTRING_INDEX(version, ".", 2)
	AS cnt
	FROM match_info)
AS result
;
