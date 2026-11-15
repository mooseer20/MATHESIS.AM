const items = [['Method', 'Rationalization'], ['Iterations', '1 step'], ['Final answer', '1'], ['Confidence', '100%']];

export default function Metrics() {
  return (
    <div className="metrics">
      {items.map(([label, value]) => (
        <div key={label} className="panel metric">
          <span className="muted">{label}</span>
          <strong>{value}</strong>
        </div>
      ))}
    </div>
  );
}