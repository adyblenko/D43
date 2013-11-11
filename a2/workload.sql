SET enable_nestloop TO FALSE;
SET enable_mergejoin TO FALSE;

SELECT * FROM R
	JOIN S ON R.id = S.id;
