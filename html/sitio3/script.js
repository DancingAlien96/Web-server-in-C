// Array para almacenar los nombres
let names = [];

// Referencias a los elementos del DOM
const nameInput = document.getElementById('nameInput');
const addButton = document.getElementById('addButton');
const nameList = document.getElementById('nameList');
const selectButton = document.getElementById('selectButton');
const selectedName = document.getElementById('selectedName');

// Función para agregar un nombre a la lista
function addName() {
    const name = nameInput.value.trim();

    // Verifica que el nombre no esté vacío y que no esté ya en la lista
    if (name !== "" && !names.includes(name)) {
        names.push(name);
        updateNameList(); // Actualiza la lista de nombres en la UI
        nameInput.value = ""; // Limpia el campo de entrada
    } else if (name === "") {
        alert("Ingresa un nombre válido.");
    } else {
        alert("Ese nombre ya está en la lista.");
    }
}

// Función para actualizar la lista de nombres en el DOM
function updateNameList() {
    nameList.innerHTML = ""; // Limpia la lista
    names.forEach(name => {
        const li = document.createElement('li');
        li.textContent = name;
        nameList.appendChild(li);
    });
}

// Función para seleccionar un nombre al azar y eliminarlo de la lista
function selectRandomName() {
    if (names.length === 0) {
        alert("No hay nombres en la lista para seleccionar.");
        return;
    }

    const randomIndex = Math.floor(Math.random() * names.length);
    const chosenName = names[randomIndex];

    selectedName.textContent = `¡El nombre seleccionado es: ${chosenName}!`;

    // Eliminar el nombre seleccionado de la lista
    names.splice(randomIndex, 1);
    updateNameList(); // Actualizar la lista en el DOM
}

// Asignar eventos a los botones
addButton.addEventListener('click', addName);
selectButton.addEventListener('click', selectRandomName);

// Permitir agregar nombre al presionar Enter
nameInput.addEventListener('keypress', function(event) {
    if (event.key === "Enter") {
        addName();
    }
});
