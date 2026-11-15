import { Check, Repeat, Sigma, ShieldCheck } from 'lucide-react';

const items = [
  { label: 'Մեթոդ', value: 'Ռացիոնալացում', icon: Check },
  { label: 'Իտերացիաներ', value: '1 քայլ', icon: Repeat },
  { label: 'Վերջնական պատասխան', value: '1', icon: Sigma },
  { label: 'Վստահություն', value: '100%', icon: ShieldCheck },
];

export default function Metrics() {
  return (
    <div className="metrics">
      {items.map(({ label, value, icon: Icon }) => (
        <div key={label} className="panel metric">
          <span className="icon-dot"><Icon size={18} /></span>
          <div className="metric-text"><span className="muted">{label}</span><strong>{value}</strong></div>
        </div>
      ))}
    </div>
  );
}