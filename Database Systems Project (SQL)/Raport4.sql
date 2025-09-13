-- Raport de complexitate  : 4 * JOIN +  WHERE + GROUP BY + HAVING
-- Acesta calculeaza venitul total pentru fiecare ingredient utilizat in preparatele comandate, pe baza cantitatii si a pretului. 
-- Am ales doar comenzile finalizate, care conțin mai mult de 3 preparate si  doar ingredientele care au fost utilizate in cel putin trei preparate distincte.

USE RestoDB;
GO


CREATE PROCEDURE GetVenitIngredient
AS
BEGIN
    SET NOCOUNT ON;

    SELECT 
        i.Denumire_ingredient AS Ingredient,
        SUM(ip.cantitate * p.pret) AS Venit_total
		FROM Ingredient i
    JOIN Ingrediente_Preparat ip ON i.ID_ingredient = ip.ID_ingredient
    JOIN Preparat p ON ip.ID_preparat = p.ID_preparat
    JOIN Preparat_Comanda pc ON p.ID_preparat = pc.ID_preparat
    JOIN Comanda c ON pc.ID_comanda = c.ID_comanda
    WHERE c.status_comanda = 'Finalizata'
    GROUP BY i.Denumire_ingredient
	HAVING COUNT(DISTINCT p.ID_preparat) > 1
    ORDER BY Venit_total DESC;
END;
GO

EXEC GetVenitIngredient;



USE RestoDB;
GO

CREATE VIEW Vw_VenitIngredient AS
SELECT 
    i.Denumire_ingredient AS Ingredient,
    SUM(ip.cantitate * p.pret) AS Venit_total
FROM Ingredient i
JOIN Ingrediente_Preparat ip ON i.ID_ingredient = ip.ID_ingredient
JOIN Preparat p ON ip.ID_preparat = p.ID_preparat
JOIN Preparat_Comanda pc ON p.ID_preparat = pc.ID_preparat
JOIN Comanda c ON pc.ID_comanda = c.ID_comanda
WHERE c.status_comanda = 'Finalizata'
GROUP BY i.Denumire_ingredient
HAVING COUNT(DISTINCT p.ID_preparat) > 1;
GO
