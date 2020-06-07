DROP DATABASE IF EXISTS Nutzerdaten;
CREATE DATABASE Nutzerdaten;
USE Nutzerdaten;

CREATE TABLE `EmpfangeneNachricht` (
  `AbsenderID` int(11),
  `EmpfaengerID` int(11),
  `Zeit` int(11),
  `Nachricht` varchar(255),
  `EmpgangenGruppenID` int(4)
);

CREATE TABLE `GesendeteNachricht` (
  `GAbsenderID` int(11),
  `GEmpfaengerID` int(11),
  `GNachricht` varchar(255)
);

CREATE TABLE `Nutzer` (
  `Name` varchar(20),
  `Passwort` varchar(50),
  `NutzerID` int(11) AUTO_INCREMENT,
  PRIMARY KEY (`NutzerID`)
);

CREATE TABLE `Gruppe` (
  `GruppeNutzerID` int(11),
  `GruppenID` int(4),
  FOREIGN KEY(GruppeNutzerID) REFERENCES Nutzer(NutzerID)
);
