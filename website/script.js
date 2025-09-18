async function updateData() {
  const response = await fetch('/api/weather');
  const data = await response.json();
  document.getElementById('temp').textContent = data.temperature || '--';
  document.getElementById('humid').textContent = data.humidity || '--';
}

setInterval(updateData, 1000);
updateData();