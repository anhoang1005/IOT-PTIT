SELECT id, time, nhietdo, doam, CAST(anhsang AS FLOAT) AS anhsang_int
FROM ThongSo
ORDER BY anhsang_int DESC
OFFSET 0 ROWS
FETCH NEXT 10 ROWS ONLY;
