-- Raport de complexitate 6 : 3 * JOIN + WHERE + GROUP BY + HAVING
--Acest raport prezintă meniurile pentru care totalul vânzărilor a depaseasca 100

CREATE PROCEDURE GetTotalVanzari
AS
BEGIN
    SET NOCOUNT ON;

    SELECT 
        m.Denumire AS Meniu,
        SUM(pc.cantitate * pr.Pret) AS Total_vanzari
    FROM Meniu m
    JOIN Preparat pr ON m.ID_meniu = pr.ID_meniu
    JOIN Preparat_Comanda pc ON pr.ID_preparat = pc.ID_preparat
    JOIN Comanda c ON pc.ID_comanda = c.ID_comanda
    WHERE c.Status_comanda = 'Finalizata'
    AND m.Data_inceput <= GETDATE() 
    AND (m.Data_sfarsit >= GETDATE())
    GROUP BY m.Denumire
	HAVING SUM(pc.cantitate * pr.Pret) > 100 
    ORDER BY Total_vanzari DESC;
END;
GO

EXEC GetTotalVanzari;




USE RestoDB;
GO

CREATE VIEW Vw_TotalVanzari AS
SELECT 
    m.Denumire AS Meniu,
    SUM(pc.cantitate * pr.Pret) AS Total_vanzari
FROM Meniu m
JOIN Preparat pr ON m.ID_meniu = pr.ID_meniu
JOIN Preparat_Comanda pc ON pr.ID_preparat = pc.ID_preparat
JOIN Comanda c ON pc.ID_comanda = c.ID_comanda
WHERE c.Status_comanda = 'Finalizata'
AND m.Data_inceput <= GETDATE() 
AND m.Data_sfarsit >= GETDATE()
GROUP BY m.Denumire
HAVING SUM(pc.cantitate * pr.Pret) > 100;
GO
