// Tipos de fantasmas y sus descripciones
const ghostTypes = [
    { name: "Poltergeist", description: "Un fantasma ruidoso y travieso que puede mover objetos y causar disturbios." },
    { name: "Fantasmas de Aparición", description: "Aparecen como figuras translúcidas que vagan por lugares antiguos, reviviendo sus últimos momentos." },
    { name: "Fantasmas Vengativos", description: "Seres llenos de odio y venganza, buscando ajustar cuentas con los vivos." },
    { name: "Espectros de Energía", description: "Energía residual de personas fallecidas, que se manifiestan como luces o niebla." }
];

// Función para seleccionar un fantasma aleatorio y mostrar su descripción
function getRandomGhostInfo() {
    const randomIndex = Math.floor(Math.random() * ghostTypes.length);
    return ghostTypes[randomIndex];
}

// Evento para descubrir qué tipo de fantasma acecha
document.getElementById('discoverButton').addEventListener('click', function() {
    const ghostInfo = getRandomGhostInfo();

    // Detectar si el usuario está en una pantalla de móvil
    if (window.innerWidth < 768) {
        alert(`¡Cuidado! Te acecha un ${ghostInfo.name}. ${ghostInfo.description}`);  // Mostrar un alert en móvil
    } else {
        document.getElementById('result').textContent = `¡Cuidado! Te acecha un ${ghostInfo.name}. ${ghostInfo.description}`;  // Mostrar el resultado en el DOM en desktop
    }
});
