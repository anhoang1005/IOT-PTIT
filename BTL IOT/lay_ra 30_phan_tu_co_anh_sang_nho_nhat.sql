SELECT TOP 30 id, time, nhietdo, doam, CAST(anhsang AS INT) AS anhsang_int
FROM ThongSo
ORDER BY anhsang_int ASC;
