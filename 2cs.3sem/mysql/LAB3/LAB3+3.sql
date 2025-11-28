SELECT SpectralClass, COUNT(*) AS StarCount  
FROM Stars
GROUP BY SpectralClass
HAVING StarCount = (
    SELECT MIN(StarCount)
    FROM (
        SELECT COUNT(*) AS StarCount
        FROM Stars
        GROUP BY SpectralClass
    ) AS Counts
);
