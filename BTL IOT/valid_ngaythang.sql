SELECT id, time, doituong, trangthai
FROM Lichsu
WHERE TRY_CONVERT(datetime, time, 103) >= '2023-11-03 00:00:00'
AND TRY_CONVERT(datetime, time, 103) <= '2023-11-03 01:00:00';
