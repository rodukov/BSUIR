SELECT 
    Constellation,
    MIN(MassSun) AS MinMass,
    MAX(MassSun) AS MaxMass,
    AVG(MassSun) AS AvgMass
FROM Stars
GROUP BY Constellation;
