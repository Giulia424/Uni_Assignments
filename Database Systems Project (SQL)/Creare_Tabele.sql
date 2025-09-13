
-- Crearea tabelului Meniu
CREATE TABLE Meniu (
    Id_Meniu INT PRIMARY KEY IDENTITY(1,1),
    Denumire VARCHAR(30) NOT NULL,
    Descriere VARCHAR(40) NULL,
    Data_Inceput DATETIME NULL,
    Data_Sfarsit DATETIME NULL
);
-- Crearea tabelului Preparat
CREATE TABLE Preparat (
    Id_Preparat INT PRIMARY KEY IDENTITY(1,1),
    Id_Meniu INT NULL,
    Denumire VARCHAR(100) NOT NULL,
    Descriere VARCHAR(255) NULL,
	Categorie VARCHAR(50) CHECK (Categorie IN ('Aperitiv', 'Fel principal', 'Desert', 'Bautura')) NOT NULL,
    Pret INT NOT NULL,
    FOREIGN KEY (Id_Meniu) REFERENCES MENIU(Id_Meniu) ON DELETE SET NULL
);

-- Crearea tabelului Comanda
CREATE TABLE Comanda (
    Id_Comanda INT PRIMARY KEY IDENTITY(1,1),
    Nr_Masa INT NOT NULL,
    Data_Comanda DATETIME NOT NULL,
    Status_Comanda VARCHAR(50) CHECK (Status_Comanda IN ('In procesare', 'Finalizata', 'Anulata')) NOT NULL
);

-- Crearea tabelului Preparat_Comanda
CREATE TABLE Preparat_comanda (
    Id_Comanda INT,
    Id_Preparat INT,
    Cantitate INT CHECK (Cantitate > 0) NOT NULL,
    PRIMARY KEY (Id_Comanda, Id_Preparat),
    FOREIGN KEY (Id_Comanda) REFERENCES COMANDA(Id_Comanda) ON DELETE CASCADE,
    FOREIGN KEY (Id_Preparat) REFERENCES PREPARAT(Id_Preparat) ON DELETE CASCADE
);

-- Crearea tabelului Ingredient
CREATE TABLE Ingredient (
    Id_Ingredient INT PRIMARY KEY IDENTITY(1,1),
    Denumire_Ingredient VARCHAR(100) NOT NULL,
    Descriere_Ingredient TEXT NULL,
    Unitate VARCHAR(50) NOT NULL
);

-- Crearea tabelului Ingrediente_Preparat
CREATE TABLE Ingrediente_preparat (
    Id_Preparat INT,
    Id_Ingredient INT,
    Cantitate DECIMAL(10,2) CHECK (Cantitate > 0) NOT NULL,
    PRIMARY KEY (Id_Preparat, Id_Ingredient),
    FOREIGN KEY (Id_Preparat) REFERENCES PREPARAT(Id_Preparat) ON DELETE CASCADE,
    FOREIGN KEY (Id_Ingredient) REFERENCES INGREDIENT(Id_Ingredient) ON DELETE CASCADE
);
