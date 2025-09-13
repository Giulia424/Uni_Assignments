-- Raport de complexitate 7 : 3 * JOIN + 2 * WHERE + GROUP BY + HAVING
-- Procedura va returna meniurile și categoriile de preparate care au generat un venit total mai mare de 50 și care provin din comenzi cu mai mult de 3 preparate

USE RestoDB;
GO


CREATE PROCEDURE GetVenitCategorie
AS
BEGIN
    SET NOCOUNT ON;

    SELECT 
        m.Denumire AS Meniu,
        pr.Categorie,
        SUM(pc.Cantitate * pr.Pret) AS Venit_total
    FROM Meniu m
    JOIN Preparat pr ON m.ID_meniu = pr.ID_meniu
    JOIN Preparat_Comanda pc ON pr.ID_preparat = pc.ID_preparat
    JOIN Comanda c ON pc.ID_comanda = c.ID_comanda
    WHERE c.Status_comanda = 'Finalizata'
    AND (SELECT COUNT(*) FROM Preparat_Comanda pc2 WHERE pc2.ID_comanda = c.ID_comanda) > 3
    GROUP BY m.Denumire, pr.Categorie
    HAVING SUM(pc.Cantitate * pr.Pret) > 50  
    ORDER BY Venit_total DESC;
END;
GO
EXEC GetVenitCategorie;


USE RestoDB;
GO

CREATE VIEW Vw_VenitCategorie AS
SELECT 
    m.Denumire AS Meniu,
    pr.Categorie,
    SUM(pc.Cantitate * pr.Pret) AS Venit_total
FROM Meniu m
JOIN Preparat pr ON m.ID_meniu = pr.ID_meniu
JOIN Preparat_Comanda pc ON pr.ID_preparat = pc.ID_preparat
JOIN Comanda c ON pc.ID_comanda = c.ID_comanda
WHERE c.Status_comanda = 'Finalizata'
AND (SELECT COUNT(*) FROM Preparat_Comanda pc2 WHERE pc2.ID_comanda = c.ID_comanda) > 3
GROUP BY m.Denumire, pr.Categorie
HAVING SUM(pc.Cantitate * pr.Pret) > 50;
GO
