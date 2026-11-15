const tabs = ['Solution', '3D Visualization', '2D Graph', 'Iteration View'];

export default function VizPanel() {
  return (
    <section className="panel">
      <div className="tabs">
        {tabs.map((t, i) => (
          <span key={t} className={i === 0 ? 'tab active' : 'tab'}>{t}</span>
        ))}
      </div>
      <div className="placeholder">3D surface</div>
      <div className="placeholder small">2D graph (along y = 0)</div>
    </section>
  );
}