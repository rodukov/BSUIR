SELECT StarName, MassSun
FROM stars
WHERE Constellation = 'Орион'
AND MassSun = (
	SELECT MIN(MassSun)
	FROM Stars
	WHERE Constellation = 'Орион'
);
