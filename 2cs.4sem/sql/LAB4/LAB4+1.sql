CREATE TABLE IF NOT EXISTS test (
	id INTEGER,
	val INTEGER
);

INSERT INTO test VALUES (1, 100), (2, 100), (3, 0);

SELECT * FROM test;

DO $$
DECLARE
    v_v1 NUMERIC;
    v_v2 NUMERIC;
    v_v3 NUMERIC;
BEGIN

    SELECT val INTO v_v1 FROM test WHERE id = 1;
    UPDATE test 
    SET val = val + v_v1 
    WHERE id = 2 
    RETURNING val INTO v_v2;


	UPDATE test 
	SET val = 0 
	WHERE id = 1;

    UPDATE test 
    SET val = v_v1 * 0.10 
    WHERE id = 3 
    RETURNING val INTO v_v3;


    IF v_v1 < 0 OR v_v2 < 0 OR v_v3 < 0 THEN
        ROLLBACK;
    ELSE
        COMMIT;
    END IF;

END $$;

SELECT * FROM test;