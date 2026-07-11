/* Shared MB102 + ESP32 breadboard renderer — config per project HTML */
(function (global) {
  const MAIN_ROWS = 65;
  const CLUSTER_SIZE = 5;
  const CLUSTER_COUNT = 10;
  const RAIL_ROWS = CLUSTER_SIZE * CLUSTER_COUNT;

  const COLS_L = ["a", "b", "c", "d", "e"];
  const COLS_R = ["f", "g", "h", "i", "j"];

  const esp32L = {
    2: "3V3", 3: "GND", 4: "D15", 5: "D2", 6: "D4", 7: "RX2", 8: "TX2",
    9: "D5", 10: "D18", 11: "D19", 12: "D21", 13: "RX0", 14: "TX0", 15: "D22", 16: "D23"
  };

  const esp32R = {
    2: "VIN", 3: "GND", 4: "D13", 5: "D12", 6: "D14", 7: "D27", 8: "D26",
    9: "D25", 10: "D33", 11: "D32", 12: "D35", 13: "D34", 14: "VN", 15: "VP", 16: "EN"
  };

  function renderHeader(hdrEl) {
    hdrEl.innerHTML = [
      "<span>−</span>", "<span>+</span>",
      "<span>#</span>",
      ...COLS_L.map(c => `<span>${c}</span>`),
      "<span>‖</span>",
      ...COLS_R.map(c => `<span>${c}</span>`),
      "<span>#</span>",
      "<span>+</span>", "<span>−</span>"
    ].join("");
  }

  function renderBoard(boardEl, options) {
    const espPins = options.espPins || new Set();
    const wiring = options.wiring || {};

    boardEl.innerHTML = "";

    for (let r = 1; r <= MAIN_ROWS; r++) {
      if (r > 1 && r <= RAIL_ROWS && (r - 1) % CLUSTER_SIZE === 0) {
        const gap = document.createElement("div");
        gap.className = "bb-row cluster-gap";
        gap.innerHTML = "<div></div>".repeat(16);
        boardEl.appendChild(gap);
      }

      const row = document.createElement("div");
      row.className = "bb-row";
      row.dataset.row = r;

      const inRail = r <= RAIL_ROWS;
      const clusterIdx = Math.floor((r - 1) / CLUSTER_SIZE);

      row.appendChild(railCell(inRail, "minus", r, clusterIdx));
      row.appendChild(railCell(inRail, "plus", r, clusterIdx));

      const numL = document.createElement("div");
      numL.className = "row-num";
      numL.textContent = r;
      row.appendChild(numL);

      for (const col of COLS_L) {
        row.appendChild(mainCell(r, col, "L", espPins, wiring));
      }

      const trench = document.createElement("div");
      trench.className = "main-hole trench";
      row.appendChild(trench);

      for (const col of COLS_R) {
        row.appendChild(mainCell(r, col, "R", espPins, wiring));
      }

      const numR = document.createElement("div");
      numR.className = "row-num";
      numR.textContent = r;
      row.appendChild(numR);

      row.appendChild(railCell(inRail, "plus", r, clusterIdx));
      row.appendChild(railCell(inRail, "minus", r, clusterIdx));

      boardEl.appendChild(row);
    }
  }

  function railCell(active, kind, row, clusterIdx) {
    const el = document.createElement("div");
    el.className = "rail-hole";
    if (!active) {
      el.classList.add("empty");
      return el;
    }
    el.classList.add(kind);
    el.title = `Rail ${kind === "plus" ? "+" : "−"} · cụm ${clusterIdx + 1} · hàng ${row}`;
    return el;
  }

  function mainCell(row, col, side, espPins, wiring) {
    const el = document.createElement("div");
    el.className = "main-hole";
    el.title = `${col}${row}`;

    const pin = side === "L" ? esp32L[row] : esp32R[row];
    const espCol = side === "L" ? col === "b" : col === "j";
    if (pin && espCol) {
      el.classList.add("esp32");
      el.textContent = pin;
    }

    const id = `${row}${col}`;
    if (espPins.has(id)) el.classList.add("mark");
    const w = wiring[id];
    if (w) el.classList.add(...w.split(" "));
    return el;
  }

  function render(hdrEl, boardEl, options) {
    renderHeader(hdrEl);
    renderBoard(boardEl, options || {});
  }

  global.RobotLabBreadboard = { render, esp32L, esp32R };
})(window);
