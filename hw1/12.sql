SELECT v, SUM(ban_cnt) v_total_ban
FROM(
	SELECT v, c_n, COUNT(*) ban_cnt
	FROM(
		SELECT DISTINCT SUBSTRING_INDEX(M.version, ".", 1) v, B.m_i m_i, B.c_i c_i, C.champion_name c_n
		FROM match_info M
		JOIN(
			SELECT match_id m_i, champion_id c_i
			FROM teamban
		) B ON (M.match_id = B.m_i)
		JOIN champ C ON (B.c_i = C.champion_id)
	) V_Cname
	GROUP BY v, c_n
	ORDER BY ban_cnt
) V_CN_BanCnt
GROUP BY v;

SELECT v, c_n, COUNT(*) ban_cnt, COUNT(*)/13267 ban_ratio
FROM(
	SELECT DISTINCT SUBSTRING_INDEX(M.version, ".", 1) v, B.m_i m_i, B.c_i c_i, C.champion_name c_n
	FROM match_info M
	JOIN(
		SELECT match_id m_i, champion_id c_i
		FROM teamban
	) B ON (M.match_id = B.m_i)
	JOIN champ C ON (B.c_i = C.champion_id)
	WHERE SUBSTRING_INDEX(M.version, ".", 1) = "4"
) V_Cname
GROUP BY v, c_n
ORDER BY ban_ratio DESC
LIMIT 5
;

SELECT v, c_n, COUNT(*) ban_cnt, COUNT(*)/21856 ban_ratio
FROM(
	SELECT DISTINCT SUBSTRING_INDEX(M.version, ".", 1) v, B.m_i m_i, B.c_i c_i, C.champion_name c_n
	FROM match_info M
	JOIN(
		SELECT match_id m_i, champion_id c_i
		FROM teamban
	) B ON (M.match_id = B.m_i)
	JOIN champ C ON (B.c_i = C.champion_id)
	WHERE SUBSTRING_INDEX(M.version, ".", 1) = "5"
) V_Cname
GROUP BY v, c_n
ORDER BY ban_ratio DESC
LIMIT 5
;

SELECT v, c_n, COUNT(*) ban_cnt, COUNT(*)/24050 ban_ratio
FROM(
	SELECT DISTINCT SUBSTRING_INDEX(M.version, ".", 1) v, B.m_i m_i, B.c_i c_i, C.champion_name c_n
	FROM match_info M
	JOIN(
		SELECT match_id m_i, champion_id c_i
		FROM teamban
	) B ON (M.match_id = B.m_i)
	JOIN champ C ON (B.c_i = C.champion_id)
	WHERE SUBSTRING_INDEX(M.version, ".", 1) = "6"
) V_Cname
GROUP BY v, c_n
ORDER BY ban_ratio DESC
LIMIT 5
;

SELECT v, c_n, COUNT(*) ban_cnt, COUNT(*)/1030786 ban_ratio
FROM(
	SELECT DISTINCT SUBSTRING_INDEX(M.version, ".", 1) v, B.m_i m_i, B.c_i c_i, C.champion_name c_n
	FROM match_info M
	JOIN(
		SELECT match_id m_i, champion_id c_i
		FROM teamban
	) B ON (M.match_id = B.m_i)
	JOIN champ C ON (B.c_i = C.champion_id)
	WHERE SUBSTRING_INDEX(M.version, ".", 1) = "7"
) V_Cname
GROUP BY v, c_n
ORDER BY ban_ratio DESC
LIMIT 5
;

SELECT v, COUNT(*) cnt
FROM teamban T
JOIN(
	SELECT DISTINCT SUBSTRING_INDEX(version, ".", 1) v, match_id m_i
	FROM match_info
	WHERE SUBSTRING_INDEX(version, ".", 1) = "7"
) M ON (T.match_id = M.m_i)
WHERE champion_id = 429
GROUP BY v
;



