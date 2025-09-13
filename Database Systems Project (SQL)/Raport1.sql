-- Raport de Complexitate 4: 2 *JOIN, WHERE, GROUP BY
-- Acest raport oferă informații despre preparatele care au fost comandate cel mai frecvent, pe categorie (Aperitiv, Fel principal, Desert, Bautura).

USE RestoDB;
GO

CREATE PROCEDURE Aperitive_Frecvente
AS
BEGIN
    SET NOCOUNT ON;
    SELECT 
		m.Denumire AS Meniu,
        p.Categorie,
        p.Denumire ,
        SUM(pc.Cantitate) AS Numar_Comenzi
    FROM Preparat_Comanda pc
    JOIN Preparat p ON pc.ID_preparat = p.ID_preparat
    JOIN Meniu m ON p.ID_meniu = m.ID_meniu
	WHERE p.Categorie = 'Aperitiv'
	GROUP BY m.Denumire, p.Categorie, p.Denumire
    ORDER BY p.Categorie, Numar_Comenzi DESC;
END;
GO

EXEC Aperitive_Frecvente

USE RestoDB;
GO

CREATE VIEW Vw_Aperitive_Frecvente AS
SELECT 
    m.Denumire AS Meniu,
    p.Categorie,
    p.Denumire,
    SUM(pc.Cantitate) AS Numar_Comenzi
FROM Preparat_Comanda pc
JOIN Preparat p ON pc.ID_preparat = p.ID_preparat
JOIN Meniu m ON p.ID_meniu = m.ID_meniu
WHERE p.Categorie = 'Aperitiv'
GROUP BY m.Denumire, p.Categorie, p.Denumire;
GO
