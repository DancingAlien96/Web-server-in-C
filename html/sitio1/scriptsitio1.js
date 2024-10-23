// Array de razas alienígenas para el botón de descubrir
const alienRaces = ['Gris', 'Reptiliano', 'Nórdico', 'Anunnaki'];

// Función para seleccionar una raza aleatoria
function getRandomAlienRace() {
    const randomIndex = Math.floor(Math.random() * alienRaces.length);
    return alienRaces[randomIndex];
}

// Evento para descubrir qué raza alienígena eres
document.getElementById('discoverButton').addEventListener('click', function() {
    const result = getRandomAlienRace();

    // Detectar si el usuario está en una pantalla de móvil
    if (window.innerWidth < 768) {
        alert(`¡Eres un ${result}!`);  // Mostrar un alert en móvil
    } else {
        document.getElementById('result').textContent = `¡Eres un ${result}!`;  // Mostrar el resultado en el DOM en desktop
    }
});
