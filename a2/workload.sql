SET enable_nestloop TO TRUE;
SET enable_mergejoin TO TRUE;

EXPLAIN SELECT * FROM R
	JOIN S ON R.id = S.id;